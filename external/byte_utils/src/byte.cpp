#include "../include/byte.h"

#include <iomanip>
#include <exception>
#include <sstream>

namespace ByteUtils {

Byte::Byte(const std::bitset<8> byte): byte_(byte) {}

Byte::Byte(std::uint8_t data): byte_(data) {}

Byte::Byte(const std::string& data, const uint8_t base) {
  if (base !=2 && base!=16) {
    throw std::invalid_argument("Representation can be made only for binary "
                                "or hexadecimal values.");
  }
  if (base == 16 && data.size() > 2) {
    throw std::invalid_argument("Given hexadecimal data can't be represented " 
                                "in 1 byte.");
  }
  if (base == 2 && data.size() > 8) {
    throw std::invalid_argument("Given binary data can't be represented " 
                                "in 1 byte.");
  }
  std::uint8_t bites = std::stoul(data, nullptr, base);
  byte_ = bites;
}

std::ostream& operator<<(std::ostream& stream, const Byte data) {
  stream << data.GetByte();
  return stream;
}

const Byte Byte::operator&(const Byte data) const {
  return byte_ & data.byte_;
}

const Byte Byte::operator|(const Byte data) const {
  return byte_ | data.byte_;
}

const Byte Byte::operator^(const Byte data) const {
  return byte_ ^ data.byte_;
}

Byte& Byte::operator^=(const Byte data) {
  byte_ ^= data.byte_;
  return *this;
}

const Byte Byte::operator<<(const std::size_t n_pos) const {
  return byte_ << n_pos;
}

Byte& Byte::operator<<=(const std::size_t n_pos) {
  byte_ <<= n_pos;
  return *this;
}

Byte& Byte::operator>>=(const std::size_t n_pos) {
  byte_ >>= n_pos;
  return *this;
}

const Byte Byte::operator*(Byte byte2) {
  Byte result;
  Byte byte1(byte_);
  while (byte2) {
    // Checks if LSB is set to `1`.
    if (byte2 & Byte(1)) {
      result ^= byte1;
    }
    byte2 >>= 1;
    // Checks if MSB is set to `1`.
    if (byte1 & Byte(0x80)) {
      byte1 <<= 1;
      // Reducing using the irreducible polynomial.
      byte1 ^= 0x1b;
      continue;
    }
    byte1 <<= 1;
  }
  return result ;
}

const std::string Byte::ToHex() const {
  std::stringstream stream;
  stream << std::hex << std::setw(2) << std::setfill('0') << byte_.to_ulong();
  return stream.str();
}

}  // namespace ByteUtils