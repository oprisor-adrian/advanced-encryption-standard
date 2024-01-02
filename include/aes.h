/* 
  Copyright (C) 2023-2024 Oprișor Adrian-Ilie
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
   
  Contact: contact@dev-adrian.com
*/
#ifndef AES_AES_H_
#define AES_AES_H_

#include <byte_vector.h>
#include <word.h>

namespace Cryptography {

// The `AES` class provides an implementation of the Rijdael block cipher.
// Example:
//    std::string key = "";
//    std::string plain_text = "";
//    Cryptography::AES aes;
//    std::string cipher_text = aes.Encrypt(plain_text, key);
class AES {
  public:
    AES() = default;
    // Returns encrypted `plain` text by applying the AES block cipher.
    const ByteUtils::ByteVector& Encrypt(const ByteUtils::ByteVector& plain,
                                         const ByteUtils::ByteVector& key);
    // Returns decrypted `cipher` text by applying 
    // the inverse of the AES block cipher.
    const ByteUtils::ByteVector& Decrypt(const ByteUtils::ByteVector& cipher,
                                         const ByteUtils::ByteVector& key);
  private:
    // Expands the key to generate a key schedule.
    void KeyExpansion();
    // Applies the `s-box` on a 4 byte `Word` object.
    ByteUtils::Word<32> SubWord(const ByteUtils::Word<32>& word);
    // Performs a cyclic permutation on a 4 byte `Word` object.
    ByteUtils::Word<32> RotWord(const ByteUtils::Word<32>& word);
    // Adds scheduled key to the %state_. 
    void AddRoundKey(std::size_t round);
    // Substituts the bytes from the %state_ with values from `s-box`.
    void SubByte();
    void InvSubByte();
    // Cyclically shifts the %state_ bytes over a different number of bytes.
    void ShiftCols();
    void InvShiftCols();
    // Transforms the columns of the %state_ using polynomical multiplication.
    void MixColumns();
    void InvMixColumns();
    // Initiates the number of rounds and the number of words
    // for different sizes of the input key.
    void InitVariable(std::size_t key_size);
    ByteUtils::ByteVector key_;
    ByteUtils::ByteVector state_;
    std::size_t rounds_;
    // Stores the numbers of words from the key.
    std::size_t key_wsize_;
};

}  // namespace Cryptography

#endif  // AES_AES_H_