/* 
  Copyright (C) 2023-2024 Oprișor Adrian-Ilie
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
   
  Contact: contact@dev-adrian.com
*/
#include "aes.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>

#include <byte.h>

namespace Cryptography {

namespace {

const ByteUtils::ByteVector s_box("637C777BF26B6FC53001672BFED7AB76"
                                  "CA82C97DFA5947F0ADD4A2AF9CA472C0"
                                  "B7FD9326363FF7CC34A5E5F171D83115"
                                  "04C723C31896059A071280E2EB27B275"
                                  "09832C1A1B6E5AA0523BD6B329E32F84"
                                  "53D100ED20FCB15B6ACBBE394A4C58CF"
                                  "D0EFAAFB434D338545F9027F503C9FA8"
                                  "51A3408F929D38F5BCB6DA2110FFF3D2"
                                  "CD0C13EC5F974417C4A77E3D645D1973"
                                  "60814FDC222A908846EEB814DE5E0BDB"
                                  "E0323A0A4906245CC2D3AC629195E479"
                                  "E7C8376D8DD54EA96C56F4EA657AAE08"
                                  "BA78252E1CA6B4C6E8DD741F4BBD8B8A"
                                  "703EB5664803F60E613557B986C11D9E"
                                  "E1F8981169D98E949B1E87E9CE5528DF"
                                  "8CA1890DBFE6426841992D0FB054BB16");

const ByteUtils::ByteVector inv_s_box("52096ad53036a538bf40a39e81f3d7fb"
                                      "7ce339829b2fff87348e4344c4dee9cb"
                                      "547b9432a6c2233dee4c950b42fac34e"
                                      "082ea16628d924b2765ba2496d8bd125"
                                      "72f8f66486689816d4a45ccc5d65b692"
                                      "6c704850fdedb9da5e154657a78d9d84"
                                      "90d8ab008cbcd30af7e45805b8b34506"
                                      "d02c1e8fca3f0f02c1afbd0301138a6b"
                                      "3a9111414f67dcea97f2cfcef0b4e673"
                                      "96ac7422e7ad3585e2f937e81c75df6e"
                                      "47f11a711d29c5896fb7620eaa18be1b"
                                      "fc563e4bc6d279209adbc0fe78cd5af4"
                                      "1fdda8338807c731b11210592780ec5f"
                                      "60517fa919b54a0d2de57a9f93c99cef"
                                      "a0e03b4dae2af5b0c8ebbb3c83539961"
                                      "172b047eba77d626e169146355210c7d");

const std::array<ByteUtils::Word<32>, 10> round_constant = {
  0x01000000, 0x02000000, 0x04000000, 
  0x08000000, 0x10000000, 0x20000000,
  0x40000000, 0x80000000, 0x1b000000,
  0x36000000
};

}  // namespace

const ByteUtils::ByteVector& AES::Encrypt(const ByteUtils::ByteVector& plain,
                                          const ByteUtils::ByteVector& key) {
  key_ = key;
  state_ = plain;
  InitVariable(key.Size());
  KeyExpansion();
  AddRoundKey(0);
  for (std::size_t index = 1; index < rounds_; index++) {
    SubByte();
    ShiftCols();
    MixColumns();
    AddRoundKey(index);
  }
  SubByte();
  ShiftCols();
  AddRoundKey(rounds_);
  return state_;
}

const ByteUtils::ByteVector& AES::Decrypt(const ByteUtils::ByteVector& cipher,
                                          const ByteUtils::ByteVector& key) {
  key_ = key;
  state_ = cipher;
  InitVariable(key.Size());
  KeyExpansion();
  AddRoundKey(rounds_);
  for (std::size_t index = rounds_ - 1; index > 0; index--) {
    InvShiftCols();
    InvSubByte();
    AddRoundKey(index);
    InvMixColumns();
    std::cout << state_.ToHex() << std::endl;
  }
  InvShiftCols();
  InvSubByte();
  AddRoundKey(0);
  return state_;
}

void AES::AddRoundKey(std::size_t round) {
  std::vector<ByteUtils::Word<32>> key_schedule = key_.GetWord<32>(round*4, 4);
  // Add keys schedule to each column of the state.
  for (std::size_t windex = 0; windex < 4; windex++) {
    for (std::size_t bindex = 0; bindex < 4; bindex++) {
      state_[windex * 4 + bindex] ^= key_schedule[windex][bindex];
    }
  }
}

void AES::SubByte() {
  for(std::size_t index = 0; index < state_.Size(); index++) {
    std::size_t sb_index = state_[index].ToInt(); 
    state_[index] = s_box[sb_index];
  }
}

void AES::InvSubByte() {
  for(std::size_t index = 0; index < state_.Size(); index++) {
    std::size_t inv_sb_index = state_[index].ToInt();
    state_[index] = inv_s_box[inv_sb_index];
  }
}

void AES::ShiftCols() {
  for (std::size_t cindex = 1; cindex < 4; cindex++) {
    for (std::size_t index = 0; index < cindex; index++) {
      for (std::size_t rindex = 0; rindex < 3; rindex++) {
        std::swap(state_[rindex * 4 + cindex], state_[(rindex + 1) * 4 + cindex]);
      }
    }
  }
}

void AES::InvShiftCols() {
  for (std::size_t cindex = 1; cindex < 4; cindex++) {
    for (std::size_t index = 0; index < cindex; index++) {
      for (std::size_t rindex = 3; rindex > 0; rindex--) {
        std::swap(state_[rindex * 4 + cindex], state_[(rindex - 1) * 4 + cindex]);
      }
    }
  }
}

void AES::MixColumns() {
  for (std::size_t index=  0; index < 4; index++) {
    ByteUtils::Word<32> word = state_.GetWord<32>(index);
    state_[index * 4] = (ByteUtils::Byte(0x02) * word[0]) ^
                        (ByteUtils::Byte(0x03) * word[1]) ^ 
                         word[2] ^ word[3];
    state_[index * 4 + 1] = word[0] ^
                            (ByteUtils::Byte(0x02) * word[1]) ^
                            (ByteUtils::Byte(0x03) * word[2]) ^
                            word[3];
    state_[index * 4 + 2] = word[0] ^
                            word[1] ^
                            (ByteUtils::Byte(0x02) * word[2]) ^
                            (ByteUtils::Byte(0x03) * word[3]);
    state_[index * 4 + 3] = (ByteUtils::Byte(0x03) * word[0]) ^
                            word[1] ^ 
                            word[2] ^
                            (ByteUtils::Byte(0x02) * word[3]);
  }
}

void AES::InvMixColumns() {
  for (std::size_t index=  0; index < 4; index++) {
    ByteUtils::Word<32> word = state_.GetWord<32>(index);
    state_[index * 4] = (ByteUtils::Byte(0x0e) * word[0]) ^
                        (ByteUtils::Byte(0x0b) * word[1]) ^
                        (ByteUtils::Byte(0x0d) * word[2]) ^
                        (ByteUtils::Byte(0x09) * word[3]);  
    state_[index * 4 + 1] = (ByteUtils::Byte(0x09) * word[0]) ^
                            (ByteUtils::Byte(0x0e) * word[1]) ^
                            (ByteUtils::Byte(0x0b) * word[2]) ^
                            (ByteUtils::Byte(0x0d) * word[3]);
    state_[index * 4 + 2] = (ByteUtils::Byte(0x0d) * word[0]) ^
                            (ByteUtils::Byte(0x09) * word[1]) ^
                            (ByteUtils::Byte(0x0e) * word[2]) ^
                            (ByteUtils::Byte(0x0b) * word[3]);
    state_[index * 4 + 3] = (ByteUtils::Byte(0x0b) * word[0]) ^
                            (ByteUtils::Byte(0x0d) * word[1]) ^ 
                            (ByteUtils::Byte(0x09) * word[2]) ^
                            (ByteUtils::Byte(0x0e) * word[3]);
  }
}

void AES::KeyExpansion() {
  ByteUtils::Word<32> word;
  for (std::size_t index = key_wsize_; index < 4 * (rounds_ + 1); index++) {
    word = key_.GetWord<32>(index-1);
    if (index % key_wsize_ == 0) {
      word = SubWord(RotWord(word)) ^ round_constant[index / key_wsize_ - 1];
    } else if (key_wsize_ > 6 && index % key_wsize_ == 4) {
      word = SubWord(word);
    }
    key_.PushBack(word ^ key_.GetWord<32>(index - key_wsize_));
  }
}

ByteUtils::Word<32> AES::SubWord(const ByteUtils::Word<32>& word) {
  ByteUtils::Word<32> output;
  for (std::size_t index = 0; index < 4; index++) {
    int sb_index = word[index].ToInt();
    output[index] = s_box[sb_index];
  }
  return output;
}

ByteUtils::Word<32> AES::RotWord(const ByteUtils::Word<32>& word) {
  ByteUtils::Word<32> output = word;
  for (std::size_t index = 0; index < 3; index++) {
    std::swap(output[index], output[index+1]);
  }
  return output;
}

void AES::InitVariable(std::size_t key_size) {
  switch (key_size) {
    case 16:
      rounds_ = 10;
      key_wsize_ = 4;
      break;
    case 24:
      rounds_ = 12;
      key_wsize_ = 6;
      break;
    case 32:
      rounds_ = 14;
      key_wsize_ = 8;
      break;
    default:
      throw std::invalid_argument("Invalid size of the key.");
  }
}

}   // namespace Cryptography