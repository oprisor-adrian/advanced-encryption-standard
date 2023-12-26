#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../include/aes.h"

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
  for (const auto& test : test_cases) {
    Cryptography::AES aes(test.key);
    std::string output = aes.Encrypt(test.plain_text).ToHex();
    ASSERT_STREQ(output.c_str(), test.cipher_text.c_str());
  }
}