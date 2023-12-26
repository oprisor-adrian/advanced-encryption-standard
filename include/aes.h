#ifndef BLOCK_CIPHER_AES_H_
#define BLOCK_CIPHER_AES_H_

#include "byte_vector.h"
#include "word.h"

namespace Cryptography {

// The class `AES` provides an abstract implementation
// of the Rijdael block cipher.
// Example:
//    std::string key = "";
//    Cryptography::AES aes(key);
//    std::string plain_text = "";
//    std::cout << aes.Encrypt(plain_text);
class AES {
  public:
    // Initializes the `AES` object with 128, 192 or 256 bits key.
    AES(const ByteUtils::ByteVector& key);
    // Returns encrypted `plain` text by applying the AES block cipher.
    const ByteUtils::ByteVector& Encrypt(const ByteUtils::ByteVector& plain);
  private:
    // Expands the key to generate a key schedule.
    void KeyExpansion();
    // Applies the `s-box` on a 4 byte `Word` object.
    ByteUtils::Word SubWord(const ByteUtils::Word word);
    // Performs a cyclic permutation on a 4 byte `Word` object.
    ByteUtils::Word RotWord(const ByteUtils::Word word);
    // Adds a round key to the %state_. 
    void AddRoundKey(const std::size_t round);
    // Substituts the bytes from the %state_ with values from `s-box`.
    void SubByte();
    // Cyclically shifts the %state_ bytes over a different number of bytes.
    void ShiftCols();
    // Transforms the columns of the %state_ using polynomical multiplication.
    void MixColumns();
    ByteUtils::ByteVector key_;
    ByteUtils::ByteVector state_;
    // Stores the nubers of words from the key.
    std::size_t key_wsize_;
    std::size_t rounds_;
};

}  // namespace Cryptography

#endif  // BLOCK_CIPHER_AES_H_