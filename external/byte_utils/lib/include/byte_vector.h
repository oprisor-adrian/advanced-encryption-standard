#ifndef BYTE_UTILS_BYTE_VECTOR_H_
#define BYTE_UTILS_BYTE_VECTOR_H_

#include <ostream>
#include <string>
#include <vector>

#include "byte.h"

namespace ByteUtils {

class Word;

// The `ByteVector` class manage and performs bitwise operation
// on a vector of `N` `Byte` objects.
// Example:
//    ByteUtils::ByteVector bytes("0a1b");
//    std::cout << bytes[0];
class ByteVector{
  public:
    ByteVector() = default;
    // Initializes the `ByteVector` object with a string of hexadecimal values.
    ByteVector(const std::string& hex_string);
    // Initializes the `ByteVector` object with a vector of `Byte` objects.
    ByteVector(const std::vector<Byte>& bytes);
    ByteVector(const ByteVector& other) = default;
    ByteVector(ByteVector&& other) = default;
    ByteVector& operator=(const ByteVector& other) = default;
    ByteVector& operator=(ByteVector&& other) = default;
    ~ByteVector() = default;
    // Prints the `ByteVector` objects as an array of bits.
    friend std::ostream& operator<<(std::ostream& stream, 
                                    const ByteVector& bytes);
    // Returns the `Byte` from the position `pos`.
    Byte operator[](const std::size_t pos) const;
    // Accesses the `Byte` from the position `pos`.
    Byte& operator[](const std::size_t pos);
    // Pushes back the bytes from the `Word` object.
    void PushBack(const Word& word);
    // Returns the `Word` from the position `pos`.
    Word GetWord(const std::size_t pos) const;
    // Returns a vector of size `count` by 'Word' objects.
    std::vector<Word> GetWord(const std::size_t pos, 
                              const std::size_t count) const;
    std::string ToHex() const;
    inline std::size_t GetSize() const { return bytes_.size(); }
  private:
    std::vector<Byte> bytes_;
};

}  // namespace ByteUtils

#endif  // BYTE_UTILS_BYTE_VECTOR_H_