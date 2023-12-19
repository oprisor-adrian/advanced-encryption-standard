#ifndef BYTE_UTILS_WORD_H_
#define BYTE_UTILS_WORD_H_

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

#include "byte.h"

namespace ByteUtils {

// The `Word` class manage and performs bitwise operations on 
// exact 32 bits of data, treated as a single entity.
// Example:
//    ByteUtils::Word word1("ffffffff");
//    ByteUtils::Word word2("0a0a0a0a");
//    ByteUtils::Word result = word1 ^ word2;
class Word {
  public:
    Word() = default;
    // Represents hexadecimal values to 32 bites.
    Word(const std::string& data);
    // Initialize a word with an array of exact 4 bytes of data.
    Word(const std::array<Byte, 4> data);
    friend std::ostream& operator<<(std::ostream& stream, const Word data);
    // Performs the XOR operation between two `Word` objects.
    const Word operator^(const Word word) const;
    // Performs the XOR operation between `Word` and `Byte`.
    const Word operator^(const Byte byte) const;
    // Returns a byte from position `pos`.
    const Byte operator[](const std::size_t pos) const;
    // Acces the byte from the position `pos`.
    Byte& operator[](const std::size_t pos);
    inline const std::array<Byte, 4> GetWord() const { return word_; }
  private:
    std::array<Byte, 4> word_;
};

}  // namespace ByteUtils

#endif  // BYTE_UTILS_WORD_H_