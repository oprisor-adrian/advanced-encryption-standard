#ifndef BLOCK_CIPHER_AES_H_
#define BLOCK_CIPHER_AES_H_

#include "byte_vector.h"
#include "word.h"

namespace BlockCipher {

class AES {
  public:
    AES(const ByteUtils::ByteVector& key);
    const ByteUtils::ByteVector& Encrypt(const ByteUtils::ByteVector& plain);
  private:
    void KeyExpansion();
    ByteUtils::Word SubWord(const ByteUtils::Word word);
    ByteUtils::Word RotWord(const ByteUtils::Word word);
    void AddRoundKey(const std::size_t round);
    void SubByte();
    void ShiftCols();
    void MixColumns();
    ByteUtils::ByteVector key_;
    ByteUtils::ByteVector state_;
    std::size_t key_wsize_;
    std::size_t rounds_;
};

}  // namespace BlockCipher

#endif  // BLOCK_CIPHER_AES_H_