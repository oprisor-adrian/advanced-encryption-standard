#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../include/byte_vector.h"

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