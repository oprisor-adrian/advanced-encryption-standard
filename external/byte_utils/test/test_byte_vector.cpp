#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../include/byte_vector.h"
#include "../include/word.h"

TEST(TestByteVector, TestConstructor) {
  ByteUtils::ByteVector bytes("0a1b");
  ::testing::internal::CaptureStdout();
  std::cout << bytes;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "0000101000011011";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestToHex) {
  ByteUtils::ByteVector bytes("0a1b");
  std::string output = bytes.ToHex();
  std::string expected_output = "0a1b";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestReturnByteOperator) {
  ByteUtils::ByteVector bytes("0a1b");
  std::string output = bytes[0].ToHex();
  std::string expected_output = "0a";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestAccessByteOperator) {
  ByteUtils::ByteVector bytes("0a1b");
  bytes[0] = 0xba;
  std::string output = bytes.ToHex();
  std::string expected_output = "ba1b";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestPushBackWord) {
  ByteUtils::ByteVector bytes("ff");
  ByteUtils::Word word("1a1b1c1d");
  bytes.PushBack(word);
  std::string output = bytes.ToHex();
  std::string expected_output = "ff1a1b1c1d";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestGetWord) {
  ByteUtils::ByteVector bytes("0a0b0c0d1a1b1c1d");
  ByteUtils::Word word = bytes.GetWord(1);
  std::string output = word.ToHex();
  std::string expected_output = "1a1b1c1d";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteWord, TestGetWordVector) {
  ByteUtils::ByteVector bytes("000102030405060708090a0b0c0d0e0f");
  std::vector<ByteUtils::Word> words = bytes.GetWord(1, 2);
  std::string output = "";
  for (const auto& w : words) {
    output += w.ToHex();
  }
  std::string expected_output = "0405060708090a0b";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}