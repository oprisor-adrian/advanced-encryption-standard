#ifndef BYTE_UITILS_BYTE_H_
#define BYTE_UITILS_BYTE_H_

#include <bitset>
#include <cstdint>
#include <ostream>
#include <string>

namespace ByteUtils {

// The `Byte` class mamnage and performs bitewise operations on 
// an array of exact 8 bites (1 byte).
// Examples:
//     ByteUtils::Byte byte1(0x57);
//     ByteUtils::Byte byte2("83", 16);
//     ByteUtils::Byte result = byte1 * byte2;
class Byte {
  public:
    Byte() = default;
    // Represents exact 8 bites of data.
    Byte(const std::bitset<8> byte);
    // Represents exact 8 bites of data.
    Byte(std::uint8_t data);
    // Represents exact 8 bites of `data` in given `base`,
    // where `base` can be 2 or 16.
    Byte(const std::string& data, const uint8_t base);
    friend std::ostream& operator<<(std::ostream& stream, const Byte data);
    // Performs bitwise `AND` operation between two `Bytes` objects.
    const Byte operator&(const Byte data) const;
    // Performs bitwise `OR` operation between two `Bytes` objects.
    const Byte operator|(const Byte data) const;
    // Performs bitwise `XOR` operation between two `Byte` objects.
    const Byte operator^(const Byte data) const;
    // Performs bitwise `XOR` to the current `Bytes` object.
    Byte& operator^=(const Byte data);
    // Performs left shift with `n_pos` positions.
    const Byte operator<< (const std::size_t n_pos) const;
    // Performs left shift on current `Byte` object with `n_pos` positions.
    Byte& operator<<= (const std::size_t n_pos);
    // Performs right shift on current `Byte` object with `n_pos` positions.
    Byte& operator>>= (const std::size_t n_pos);
    // Performs Galois Field multiplication between two `Byte` objects.
    const Byte operator* (Byte byte2);
    // Cheks if at least one bite is set to `1`.
    // Equivalent with `byte > 0`.
    operator bool() const { return byte_.any(); };
    inline const char ToAscii() const { return byte_.to_ulong(); }
    const std::string ToHex() const;
    inline const std::bitset<8> GetByte() const { return byte_; }
  private:
    std::bitset<8> byte_;
};

}  // namespace ByteUtils

#endif  // BYTE_UITILS_BYTE_H_