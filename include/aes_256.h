#ifndef BLOCK_CIPHER_AES_256_H_
#define BLOCK_CIPHER_AES_256_H_

#include <cstdint>
#include <vector>

#include "byte_vector.h"

namespace BlockCipher {

// AES256 class is a implementation of the Rijndael block cipher algorithm.
// Returns an encrypted input using a 256-bits key.
// Example:
//    std::string input = "00112233445566778899aabbccddeeff";
//    std::string key = "000102030405060708090a0b0c0d0e0f10 \
//                       1112131415161718191a1b1c1d1e1f";
//    BlockCipher::AES256 aes256(input, key);
//    std::cout << aes256.Encrypt();
class AES256 {
  public:
    // Initialize the key and state with specific key and input.
    AES256(const ByteVector& input, const ByteVector& key);
    // Encrypts the input using the Rijndael block cipher algorithm.
    const ByteVector Encrypt();
  private:
    // Derives the input 256-bits key into Round Keys.
    void KeyExpansion(const ByteVector& key);
    // Adds the key to the state using XOR operations.
    void AddRoundKey(const std::size_t round);
    // Applies the s-box to the state.
    void SubByte();
    void ShiftRows();
    void MixColumns();
    // Applies the s-box on 4 bytes and produce an output word.
    ByteVector SubWord(const ByteVector& word);
    // Performs a cyclic permutation on a 4 byte word.
    ByteVector RotWord(const ByteVector& word);
    // Stores the keys derived using the Key Expansion routine.
    std::vector<ByteVector> keys_;
    // Stores the intermediare results of the cipher.
    ByteVector state_;
};

}  // namespace BlockCipher
#endif  // BLOCK_CIPHER_AES_256_H_