#ifndef BYTE_UTILS_BYTE_VECTOR_H_
#define BYTE_UTILS_BYTE_VECTOR_H_

#include <ostream>
#include <string>
#include <vector>

#include "byte.h"

namespace ByteUtils {

class Word;

class ByteVector{
  public:
    ByteVector() = default;
    ByteVector(const std::string& hex_string);
    ByteVector(const std::vector<Byte> bytes);
    friend std::ostream& operator<<(std::ostream& stream, 
                                    const ByteVector& bytes);
    // Returns the `Byte` from the position `pos`.
    const Byte operator[](const std::size_t pos) const;
    // Acces the `Byte` from the position `pos`.
    Byte& operator[](const std::size_t pos);
    // Pushs back the bytes from the `Word` object.
    void PushBack(const Word word);
    // Returns the `Word` from the position `pos`.
    const Word GetWord(const std::size_t pos) const;
    // Returns `count` words from vector.
    const std::vector<Word> GetWord(const std::size_t pos, 
                                    const std::size_t count);
    const std::string ToHex() const;
    inline const std::size_t GetSize() const { return bytes_.size(); }
  private:
    std::vector<Byte> bytes_;
};

}  // namespace ByteUtils

#endif  // BYTE_UTILS_BYTE_VECTOR_H_