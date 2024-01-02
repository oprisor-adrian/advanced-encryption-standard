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
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "aes.h"

struct TestCase {
  std::string key;
  std::string plain_text;
  std::string cipher_text;
};

TEST(TestAes, TestEncrypt) {
  std::vector<TestCase> test_cases = {
    {"000102030405060708090a0b0c0d0e0f", 
     "00112233445566778899aabbccddeeff", 
     "69c4e0d86a7b0430d8cdb78070b4c55a"
    },
    {"000102030405060708090a0b0c0d0e0f1011121314151617",
     "00112233445566778899aabbccddeeff",
     "dda97ca4864cdfe06eaf70a0ec0d7191"
    },
    {"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f",
     "00112233445566778899aabbccddeeff",
     "8ea2b7ca516745bfeafc49904b496089"
    }
  };
  Cryptography::AES aes;
  for (const auto& test : test_cases) {
    std::string output = aes.Encrypt(test.plain_text, test.key).ToHex();
    ASSERT_STREQ(output.c_str(), test.cipher_text.c_str());
  }
}