#include "byte.h"

#include <iomanip>
#include <exception>
#include <sstream>

namespace ByteUtils {

Byte::Byte(const std::bitset<8>& byte): byte_(byte) {}

Byte::Byte(const std::uint8_t data): byte_(data) {}

Byte::Byte(const std::string& data, const uint8_t base) {
  if (base != 2 && base != 16) {
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
  std::uint8_t bits = std::stoul(data, nullptr, base);
  byte_ = bits;
}

std::ostream& operator<<(std::ostream& stream, const Byte& data) {
  stream << data.GetByte();
  return stream;
}

Byte Byte::operator&(const Byte& data) const {
  return byte_ & data.byte_;
}

Byte Byte::operator|(const Byte& data) const {
  return byte_ | data.byte_;
}

Byte Byte::operator^(const Byte& data) const {
  return byte_ ^ data.byte_;
}

Byte& Byte::operator^=(const Byte& data) {
  byte_ ^= data.byte_;
  return *this;
}

Byte Byte::operator<<(const std::size_t n_pos) const {
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

Byte Byte::operator*(const Byte& byte) const {
  Byte result;
  Byte byte1(byte_);
  Byte byte2(byte);
  while (byte2.IsAnySet()) {
    // Checks if LSB is set to `1`.
    Byte check_lsb = byte2 & Byte(1);
    if (check_lsb.IsAnySet()) {
      result ^= byte1;
    }
    byte2 >>= 1;
    // Checks if MSB is set to `1`.
    Byte check_msb = byte1 & Byte(0x80);
    if (check_msb.IsAnySet()) {
      byte1 <<= 1;
      // Reducing using the irreducible polynomial.
      byte1 ^= 0x1b;
      continue;
    }
    byte1 <<= 1;
  }
  return result ;
}

std::string Byte::ToHex() const {
  std::stringstream stream;
  stream << std::hex << std::setw(2) << std::setfill('0') << byte_.to_ulong();
  return stream.str();
}

}  // namespace ByteUtils