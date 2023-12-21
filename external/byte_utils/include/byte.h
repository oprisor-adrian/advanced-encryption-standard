#ifndef BYTE_UITILS_BYTE_H_
#define BYTE_UITILS_BYTE_H_

#include <bitset>
#include <cstdint>
#include <ostream>
#include <string>

namespace ByteUtils {

// The `Byte` class manage and performs bitwise operations on 
// an array of exact 8 bits.
// Example:
//     ByteUtils::Byte byte1(0x57);
//     ByteUtils::Byte byte2("83", 16);
//     ByteUtils::Byte result = byte1 * byte2;
//     std::cout << result;
class Byte {
  public:
    Byte() = default;
    // Initializes the `Byte` object with exact 8 bits of data.
    Byte(const std::bitset<8>& byte);
    // Initializes the `Byte` object with exact 8 bits of data.
    Byte(const std::uint8_t data);
    // Initializes the `Byte` object with exact 8 bits of `data`
    // in given `base`, where `base` can be 2 or 16.
    Byte(const std::string& data, const uint8_t base);
    Byte(const Byte& other) = default;
    Byte(Byte&& other) = default;
    Byte& operator=(const Byte& other) = default;
    Byte& operator=(Byte&& other) = default;
    ~Byte() = default;
    // Prints the `Byte` object as an array of bits.
    friend std::ostream& operator<<(std::ostream& stream, const Byte& data);
    // Performs bitwise `AND` operation between two `Byte` objects.
    Byte operator&(const Byte& data) const;
    // Performs bitwise `OR` operation between two `Byte` objects.
    Byte operator|(const Byte& data) const;
    // Performs bitwise `XOR` operation between two `Byte` objects.
    Byte operator^(const Byte& data) const;
    // Performs bitwise `XOR` on current `Byte` object.
    Byte& operator^=(const Byte& data);
    // Performs left shift with `n_pos` positions.
    Byte operator<<(const std::size_t n_pos) const;
    // Performs left shift on current `Byte` object with `n_pos` positions.
    Byte& operator<<=(const std::size_t n_pos);
    // Performs right shift on current `Byte` object with `n_pos` positions.
    Byte& operator>>=(const std::size_t n_pos);
    // Performs Galois Field multiplication between two `Byte` objects.
    Byte operator*(const Byte& byte) const;
    // Checks if at least one bit is set to `1`.
    inline bool IsAnySet() const { return byte_.any(); }
    inline int ToInt() const { return byte_.to_ulong(); }
    inline char ToAscii() const { return byte_.to_ulong(); }
    std::string ToHex() const;
    inline const std::bitset<8>& GetByte() const { return byte_; }
  private:
    std::bitset<8> byte_;
};

}  // namespace ByteUtils

#endif  // BYTE_UITILS_BYTE_H_