#include <gtest/gtest.h>
#include "../include/byte_vector.h"

class ByteVectorTest: public ::testing::Test {
  protected:
    void SetUp() override {
      input_hex_string_ = "000102030405060708090a0b0c0d0e0f";
      bv_ = BlockCipher::ByteVector("000102030405060708090a0b0c0d0e0f");
    }
    BlockCipher::ByteVector bv_;
    std::string input_hex_string_;
};

TEST_F(ByteVectorTest, TestPrintFunctionality) {
  ::testing::internal::CaptureStdout();
  EXPECT_NO_FATAL_FAILURE({
    std::cout << bv_;
  });
  std::string output = ::testing::internal::GetCapturedStdout();
  EXPECT_STREQ(output.c_str(), input_hex_string_.c_str());
}

TEST_F(ByteVectorTest, TestGetSize) {
  EXPECT_EQ(bv_.GetSize(), 16);
}

TEST_F(ByteVectorTest, TestAccesOperator) {
  ASSERT_NO_THROW(bv_[10]);
  EXPECT_EQ(bv_[10], std::byte(0x0a));
  ASSERT_THROW(bv_[100], std::out_of_range);
}

TEST_F(ByteVectorTest, TestAssignOperator) {
  ::testing::internal::CaptureStdout();
  EXPECT_NO_FATAL_FAILURE({
    BlockCipher::ByteVector bv1_;
    bv1_ = input_hex_string_;
    std::cout << bv1_;
  });
  std::string output = ::testing::internal::GetCapturedStdout();
  EXPECT_STREQ(output.c_str(), input_hex_string_.c_str());
}

TEST_F(ByteVectorTest, TestMultilineConstructor) {
  ::testing::internal::CaptureStdout();
  EXPECT_NO_FATAL_FAILURE({
    BlockCipher::ByteVector bv1_("00 01 02 03 \
                                  04 05 06 07 \
                                  08 09 0a 0b \
                                  0c 0d 0e 0f");
    std::cout << bv1_;
  });
  std::string output = ::testing::internal::GetCapturedStdout();
  EXPECT_STREQ(output.c_str(), input_hex_string_.c_str());
}

TEST_F(ByteVectorTest, TestConstructorByVector) {
  ::testing::internal::CaptureStdout();
  std::string str_input = "0102";
  std::vector<std::byte> input = {std::byte(0x01), std::byte(0x02)};
  BlockCipher::ByteVector bv1_(input);
  EXPECT_EQ(bv1_.GetSize(), 2);
  std::cout << bv1_;
  std::string output = ::testing::internal::GetCapturedStdout();
  EXPECT_STREQ(output.c_str(), str_input.c_str()); 
}

TEST_F(ByteVectorTest, TestRetunVectorInRange) {
  BlockCipher::ByteVector sub_vec = bv_[{0, 3}];
  EXPECT_EQ(sub_vec.GetSize(), 4);
  ::testing::internal::CaptureStdout();
  std::cout << sub_vec;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "00010203";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST_F(ByteVectorTest, TestBitwiseWithByte) {
  // Performs bitwise operation
  std::byte byte = std::byte(0x0f);
  BlockCipher::ByteVector bv1("0001");
  ::testing::internal::CaptureStdout();
  bv1 ^ byte;
  std::cout << bv1;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "0f0e";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST_F(ByteVectorTest, TestBitwiseVectors) {
  BlockCipher::ByteVector bv1("0102");
  BlockCipher::ByteVector bv2("0e0f");
  BlockCipher::ByteVector result = bv1 ^ bv2;
  ::testing::internal::CaptureStdout();
  std::cout << result;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "0f0d";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}