#include "../include/aes_256.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

namespace BlockCipher {

namespace {
  const ByteVector s_box("63 7C 77 7B F2 6B 6F C5 30 01 67 2B FE D7 AB 76 \
                          CA 82 C9 7D FA 59 47 F0 AD D4 A2 AF 9C A4 72 C0 \
                          B7 FD 93 26 36 3F F7 CC 34 A5 E5 F1 71 D8 31 15 \
                          04 C7 23 C3 18 96 05 9A 07 12 80 E2 EB 27 B2 75 \
                          09 83 2C 1A 1B 6E 5A A0 52 3B D6 B3 29 E3 2F 84 \
                          53 D1 00 ED 20 FC B1 5B 6A CB BE 39 4A 4C 58 CF \
                          D0 EF AA FB 43 4D 33 85 45 F9 02 7F 50 3C 9F A8 \
                          51 A3 40 8F 92 9D 38 F5 BC B6 DA 21 10 FF F3 D2 \
                          CD 0C 13 EC 5F 97 44 17 C4 A7 7E 3D 64 5D 19 73 \
                          60 81 4F DC 22 2A 90 88 46 EE B8 14 DE 5E 0B DB \
                          E0 32 3A 0A 49 06 24 5C C2 D3 AC 62 91 95 E4 79 \
                          E7 C8 37 6D 8D D5 4E A9 6C 56 F4 EA 65 7A AE 08 \
                          BA 78 25 2E 1C A6 B4 C6 E8 DD 74 1F 4B BD 8B 8A \
                          70 3E B5 66 48 03 F6 0E 61 35 57 B9 86 C1 1D 9E \
                          E1 F8 98 11 69 D9 8E 94 9B 1E 87 E9 CE 55 28 DF \
                          8C A1 89 0D BF E6 42 68 41 99 2D 0F B0 54 BB 16");
  const std::vector<ByteVector> round_constant = {{"01000000"},
                                                  {"02000000"},
                                                  {"04000000"},
                                                  {"08000000"},
                                                  {"10000000"},
                                                  {"20000000"},
                                                  {"40000000"},
                                                  {"80000000"},
                                                  {"1b000000"},
                                                  {"36000000"}};
  const ByteVector n_multi("0203");
}  // namespace

AES256::AES256(const ByteVector& input, const ByteVector& key) {
  // Checks the size of the input.
  if (input.GetSize() != 16) {
    throw std::invalid_argument("The input can only be 128 bits long: \
                                 input.size=" + std::to_string(input.GetSize()));
  }
  // Checks the size of the key.
  if (key.GetSize() != 32) {
    throw std::invalid_argument("The key can only be 256 bits long: \
                                 key.size=" + std::to_string(key.GetSize()));
  }
  // Initializes the state and derives the Round Keys.
  state_ = input;
  KeyExpansion(key);
}

const ByteVector AES256::Encrypt() {
  AddRoundKey(0);
  for (std::size_t index=1; index<=13; index++) {
    SubByte();
    ShiftCols();
    MixColumns();
    AddRoundKey(index);
  }
  SubByte();
  ShiftCols();
  AddRoundKey(14);
  return state_;
}

void AES256::KeyExpansion(const ByteVector& key) {
  // Initialize the keys_ vector with 4 words from input key.
  for (std::size_t index=0; index<8; index++) {
    keys_.push_back(ByteVector({key[index*4], key[index*4+1],
                                key[index*4+2], key[index*4+3]}));
  }
  // Generates the round keys.
  ByteVector temp;
  for (std::size_t index=8; index<60; index++) {
    temp = keys_[index-1];
    if (index%8==0) {
      temp = SubWord(RotWord(temp)) ^ round_constant[index/8-1];
    } else if (index%8==4) {
      temp = SubWord(temp);
    }
    keys_.push_back(temp^keys_[index-8]);
  }
}

void AES256::AddRoundKey(const std::size_t round) {
  std::vector<ByteVector> keys_schedule(keys_.begin()+(round*4), 
                                        keys_.begin()+(round*4)+4);
  // Add keys schedule to each column of the state.
  for (std::size_t windex=0; windex<4; windex++) {
    for (std::size_t bindex=0; bindex<4; bindex++) {
      state_[windex*4+bindex] ^= keys_schedule[windex][bindex];
    }
  }
}

void AES256::SubByte() {
  for(std::size_t index=0; index<state_.GetSize(); index++) {
    state_[index] = s_box[static_cast<int>(state_[index])];
  }
}

void AES256::ShiftCols() {
  for (std::size_t cindex=1; cindex<4; cindex++) {
    for (std::size_t index=0; index<cindex; index++) {
      for (std::size_t rindex=0; rindex<3; rindex++) {
        std::swap(state_[rindex*4+cindex], state_[(rindex+1)*4+cindex]);
      }
    }
  }
}

void AES256::MixColumns() {
  for (std::size_t index=0; index<state_.GetSize(); index+=4) {
    ByteVector temp = state_[{index, index+3}];
    state_[index] = GFMultiplication(n_multi[0], temp[0]) ^
                    GFMultiplication(n_multi[1], temp[1]) ^ 
                    temp[2] ^ temp[3];
    state_[index+1] = temp[0] ^
                      GFMultiplication(n_multi[0], temp[1]) ^
                      GFMultiplication(n_multi[1], temp[2]) ^
                      temp[3];
    state_[index+2] = temp[0] ^
                      temp[1] ^
                      GFMultiplication(n_multi[0], temp[2]) ^
                      GFMultiplication(n_multi[1],  temp[3]);
    state_[index+3] = GFMultiplication(n_multi[1], temp[0]) ^
                      temp[1] ^ 
                      temp[2] ^
                      GFMultiplication(n_multi[0], temp[3]);
  }
}

std::byte AES256::GFMultiplication(std::byte byte_1, std::byte byte_2) {
  uint8_t result = 0;
  uint8_t b1 = static_cast<uint8_t>(byte_1);
  uint8_t b2 = static_cast<uint8_t>(byte_2);
  while (b2 > 0) {
    if (b2 & 1) {
      result ^= b1;
    }
    if (b1 & 0x80) {
      b1 = (b1 << 1) ^ 0x1b;
    } else {
      b1 <<= 1;
    }
    b2 >>= 1;
  }
  return static_cast<std::byte>(result);
}

ByteVector AES256::SubWord(const ByteVector& word) {
  std::vector<std::byte> output_word;
  for (std::size_t index=0; index<4; index++) {
    output_word.push_back(s_box[static_cast<int>(word[index])]);
  }
  return output_word;
}

ByteVector AES256::RotWord(const ByteVector& word) {
  ByteVector output_word = word;
  for (std::size_t index=0; index<3; index++) {
    std::swap(output_word[index], output_word[index+1]);
  }
  return output_word;
}

}  // namespace BlockCipher