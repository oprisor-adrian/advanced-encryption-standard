#include <gtest/gtest.h>

#include <bitset>
#include <iostream>
#include <stdexcept>
#include <string>

#include "../include/byte.h"

TEST(TestByte, TestConstructor) {
  ASSERT_NO_THROW({ ByteUtils::Byte byte("10101100", 2); });
  ByteUtils::Byte byte("AB", 16);
  std::bitset<8> output = byte.GetByte();
  std::bitset<8> expected_output{"10101011"};
  EXPECT_EQ(output, expected_output);
}

TEST(TestByte, TestConstructorInvalidBase) {
  try {
    ByteUtils::Byte byte("15", 8);
    FAIL() << "Expected exception not thrown.";
  } catch (const std::exception& e) {
    EXPECT_STREQ("Representation can be made only for binary "
                 "or hexadecimal values.", e.what());
  }
}

TEST(TestByte, TestConstructorInvalidHexLength) {
    try {
    ByteUtils::Byte byte("ABC", 16);
    FAIL() << "Expected exception not thrown.";
  } catch (const std::exception& e) {
    EXPECT_STREQ("Given hexadecimal data can't be represented " 
                 "in 1 byte.", e.what());
  }
}

TEST(TestByte, TestConstructorInvalidBitsLength) {
    try {
    ByteUtils::Byte byte("110011011011", 2);
    FAIL() << "Expected exception not thrown.";
  } catch (const std::exception& e) {
    EXPECT_STREQ("Given binary data can't be represented " 
                 "in 1 byte.", e.what());
  }
}

TEST(TestByte, TestStdoutOverloadedOperator) {
  ByteUtils::Byte byte(0xFF);
  ::testing::internal::CaptureStdout();
  std::cout << byte;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "11111111";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST (TestByte, TestGFMultiplication) {
  ByteUtils::Byte byte1("57", 16);
  ByteUtils::Byte byte2("83", 16);
  ByteUtils::Byte result = byte1 * byte2;
  std::bitset<8> output = result.GetByte();
  std::bitset<8> expected_output{"11000001"};
  EXPECT_EQ(output, expected_output);
}