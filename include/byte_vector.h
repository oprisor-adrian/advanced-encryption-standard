#ifndef BLOCK_CIPHER_BYTE_VECTOR_H_
#define BLOCK_CIPHER_BYTE_VECTOR_H_

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

namespace BlockCipher {

// ByteVector class store a hexadecimal values as a vector of bytes.
// Example:
//    BlockCipher::ByteVector bv1("000102030405060708090a0b0c0d0e0f");
//    BlockCipher::ByteVector bv2("00 01 02 03 \
//                    04 05 06 07 \
//                    08 09 0a 0b \
//                    0c 0d 0e 0f");
//    BlockCipher::ByteVector bv3;
//    bv3 = "000102030405060708090a0b0c0d0e0f";
class ByteVector {
  public:
    // Creates an empty vector of bytes. (default)
    ByteVector() = default;
    // Creates the vector of bytes from a hexadecimal string.
    ByteVector(const std::string& hex_string);
    // Creates the vector of bytes from a vector of bytes.
    ByteVector(const std::vector<std::byte>& byte_vector);
    // Copies the vector of bytes to another one. (default)
    ByteVector(const ByteVector& other) = default;
    // Moves the vector of bytes to another one. (default)
    ByteVector(ByteVector&& other) = default;
    // Copies the vector of bytes to another one. (default operator overload)
    ByteVector& operator=(const ByteVector& other) = default;
    // Moves the vector of bytes to another one. (default operator overload)
    ByteVector& operator=(ByteVector&& other) = default;
    // Destois the vector of bytes. (default)
    ~ByteVector() = default;  
    // Prints the stored hexadecimal values.
    friend std::ostream& operator<<(std::ostream& out, const ByteVector& bv);
    // Creates the vector of bytes from a hexadecimal values passed as string.
    ByteVector& operator=(const std::string& hex_string);
    // Returns the byte from specific position.
    const std::byte operator[](const std::size_t index) const;
    // Acces the byte from specific position.
    std::byte& operator[](const std::size_t index);
    // Returns a sub vector of bytes between two positions.
    ByteVector operator[](const std::pair<std::size_t, std::size_t> rande) const; 
    // Performs bitwise operation between the vector and a byte.
    ByteVector operator^(const std::byte byte);
    // Performs bitwise operation between two vectors of same size.
    ByteVector operator^(const ByteVector& bytes) const;
    // Gets the size of the vector of bytes.
    const std::size_t GetSize() const { return byte_vector_.size(); }
  private:
    // Stores the hexadecimal values as a vector of bytes.
    std::vector<std::byte> byte_vector_;
};

}  // namespace BlockCipher
#endif  // BLOCK_CIPHER_BYTE_VECTOR_H_