#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../include/byte.h"
#include "../include/word.h"

TEST(TestWord, TestStdouOverloadedOperator) {
  ByteUtils::Word word("abffcdaf");
  ::testing::internal::CaptureStdout();
  std::cout << word;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "10101011111111111100110110101111";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestWordXorOperation) {
  ByteUtils::Word word1("ffffffff");
  ByteUtils::Word word2("0a0a0a0a");
  ByteUtils::Word result = word1 ^ word2;
  ::testing::internal::CaptureStdout();
  std::cout << result;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "11110101111101011111010111110101";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestWordByteXorOperation) {
  ByteUtils::Word word("ffffffff");
  ByteUtils::Byte byte(0x01);
  ByteUtils::Word result = word ^ byte;
  ::testing::internal::CaptureStdout();
  std::cout << result;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "11111110111111101111111011111110";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestReturnByteOperator) {
  ByteUtils::Word word("0aff0abc");
  ASSERT_THROW(word[-1], std::out_of_range);
  ByteUtils::Byte byte = word[1];
  std::bitset<8> output = byte.GetByte();
  std::bitset<8> expected_output{"11111111"};
  EXPECT_EQ(output, expected_output);
}

TEST(TestWord, TestAccesByteOPerator) {
  ByteUtils::Word word("0aff0abc");
  ASSERT_THROW(word[4], std::out_of_range);
  word[1] = ByteUtils::Byte(0x0a);
  ::testing::internal::CaptureStdout();
  std::cout << word;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "00001010000010100000101010111100";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestToHex) {
  ByteUtils::Word word("0aff0abc");
  word[3] = ByteUtils::Byte(0x0a);
  std::string output = word.ToHex();
  std::string expected_output = "0aff0a0a";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}