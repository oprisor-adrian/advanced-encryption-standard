#include <gtest/gtest.h>
#include "../include/aes_256.h"

TEST(AES256Test, TestSuite) {
  std::string input="00112233445566778899aabbccddeeff";
  std::string key="000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
  BlockCipher::AES256 aes256(input, key);
  ::testing::internal::CaptureStdout();
  std::cout << aes256.Encrypt();
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "8ea2b7ca516745bfeafc49904b496089";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}