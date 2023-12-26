/* 
  Copyright (C) 2023 Oprișor Adrian-Ilie
  
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
#include "../include/aes.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "byte.h"

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

const std::vector<ByteUtils::Word> round_constant = {{"01000000"},
                                                     {"02000000"},
                                                     {"04000000"},
                                                     {"08000000"},
                                                     {"10000000"},
                                                     {"20000000"},
                                                     {"40000000"},
                                                     {"80000000"},
                                                     {"1b000000"},
                                                     {"36000000"}};
const ByteUtils::ByteVector n_multi("0203");
}  // namespace

AES::AES(const ByteUtils::ByteVector& key): key_(key) {
  // Checks the size of key.
  switch (key.Size()) {
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

const ByteUtils::ByteVector& AES::Encrypt(const ByteUtils::ByteVector& plain) {
  state_ = plain;
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

void AES::AddRoundKey(const std::size_t round) {
  std::vector<ByteUtils::Word> key_schedule = key_.GetWord(round*4, 4);
   // Add keys schedule to each column of the state.
  for (std::size_t windex = 0; windex < 4; windex++) {
    for (std::size_t bindex = 0; bindex < 4; bindex++) {
      state_[windex * 4 + bindex] ^= key_schedule[windex][bindex];
    }
  }
}

void AES::SubByte() {
  for(std::size_t index = 0; index < state_.Size(); index++) {
    state_[index] = s_box[state_[index].ToInt()];
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

void AES::MixColumns() {
  for (std::size_t index=  0; index < 4; index++) {
    ByteUtils::Word word = state_.GetWord(index);
    state_[index * 4] = (n_multi[0] * word[0]) ^
                        (n_multi[1] * word[1]) ^ 
                        word[2] ^ word[3];
    state_[index * 4 + 1] = word[0] ^
                            (n_multi[0] * word[1]) ^
                            (n_multi[1] * word[2]) ^
                            word[3];
    state_[index * 4 + 2] = word[0] ^
                            word[1] ^
                            (n_multi[0] * word[2]) ^
                            (n_multi[1] * word[3]);
    state_[index * 4 + 3] = (n_multi[1] * word[0]) ^
                            word[1] ^ 
                            word[2] ^
                            (n_multi[0] * word[3]);
  }
}

void AES::KeyExpansion() {
  ByteUtils::Word word;
  for (std::size_t index = key_wsize_; index < 4 * (rounds_ + 1); index++) {
    word = key_.GetWord(index-1);
    if (index % key_wsize_ == 0) {
      word = SubWord(RotWord(word)) ^ round_constant[index / key_wsize_ - 1];
    } else if (key_wsize_ > 6 && index % key_wsize_ == 4) {
      word = SubWord(word);
    }
    key_.PushBack(word ^ key_.GetWord(index - key_wsize_));
  }
}

ByteUtils::Word AES::SubWord(const ByteUtils::Word word) {
  ByteUtils::Word output;
  for (std::size_t index = 0; index < 4; index++) {
    output.PushBack(s_box[word[index].ToInt()]);
  }
  return output;
}

ByteUtils::Word AES::RotWord(const ByteUtils::Word word) {
  ByteUtils::Word output = word;
  for (std::size_t index = 0; index < 3; index++) {
    std::swap(output[index], output[index+1]);
  }
  return output;
}

}   // namespace Cryptography