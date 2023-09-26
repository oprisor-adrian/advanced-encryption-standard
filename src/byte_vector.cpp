#include "../include/byte_vector.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <regex>

namespace BlockCipher {

ByteVector::ByteVector(const std::string& hex_string) {
  std::regex hex_regex("[0-9a-fA-F]{2}");
  auto regex_begin = std::sregex_iterator(hex_string.begin(), 
                                          hex_string.end(), 
                                          hex_regex);
  // Converts the string to std::vector<std::byte>.
  for (auto it=regex_begin; it!=std::sregex_iterator(); ++it) {
    std::string hex_byte = it->str();
    std::uint8_t byte = std::stoi(hex_byte, nullptr, 16);
    byte_vector_.push_back(static_cast<std::byte>(byte));
  }
}

ByteVector::ByteVector(const std::vector<std::byte>& byte_vector)
    : byte_vector_(byte_vector) {}

std::ostream& operator<<(std::ostream& out, const ByteVector& bv) {
  std::for_each(bv.byte_vector_.begin(), bv.byte_vector_.end(), 
      [&out](const auto& byte){
    out << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
  });
  out << std::dec;
  return out;
}

ByteVector& ByteVector::operator=(const std::string& hex_string) {
  std::regex hex_regex("[0-9a-fA-F]{2}");
  auto regex_begin = std::sregex_iterator(hex_string.begin(), 
                                          hex_string.end(), 
                                          hex_regex);
  // Converts the string to std::vector<std::byte>.
  for (auto it=regex_begin; it!=std::sregex_iterator(); ++it) {
    std::string hex_byte = it->str();
    std::uint8_t byte = std::stoi(hex_byte, nullptr, 16);
    byte_vector_.push_back(static_cast<std::byte>(byte));
  }
  return *this;
}

  const std::byte ByteVector::operator[](const std::size_t index) const {
    if (index > byte_vector_.size() || index < 0) {
      throw std::out_of_range("Index " + std::to_string(index) + " is out of range.");
    }
    return byte_vector_[index];
  }

  std::byte& ByteVector::operator[](const std::size_t index) {
    if (index > byte_vector_.size() || index < 0) {
      throw std::out_of_range("Index " + std::to_string(index) + " is out of range.");
    }
    return byte_vector_[index];
  }

ByteVector ByteVector::operator[]
    (const std::pair<std::size_t, std::size_t> range) const {
  // Checks the range.
  if (range.first > range.second) {
    throw std::invalid_argument("First position of the must be smaller than second.");
  }
  if (range.first < 0 || range.first > byte_vector_.size()) {
    throw std::out_of_range("First position is out of range.");
  }
  if (range.second > byte_vector_.size()) {
    throw std::out_of_range("Second position is out of range.");
  }
  std::vector<std::byte> sub_vec(byte_vector_.begin()+range.first,
                                 byte_vector_.begin()+range.second+1);
  return ByteVector(sub_vec); 
}

ByteVector ByteVector::operator^(const std::byte byte) const {
  std::vector<std::byte> result(byte_vector_);
  std::for_each(result.begin(), result.end(), [byte](auto& value){
    value ^= byte;
  });
  return ByteVector(result);
}

ByteVector ByteVector::operator^(const ByteVector& bytes) const {
  if (byte_vector_.size() != bytes.GetSize()) {
    throw std::runtime_error("In order to perform XOR operation, the vectros \
                              must have the same length.");
  }
  ByteVector result(byte_vector_);
  for (std::size_t index=0; index<result.GetSize(); index++) {
    result[index] ^= bytes[index];
  }
  return result;
}

ByteVector& ByteVector::operator^=(const std::byte byte) {
  std::for_each(byte_vector_.begin(), byte_vector_.end(), [byte](auto& value) {
    value ^= byte;
  });
  return *this;
}

}  // namespace BlockCipher