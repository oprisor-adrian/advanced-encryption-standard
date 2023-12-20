#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "include/aes.h"

int main() {
  std::string input = "00112233445566778899aabbccddeeff";
  std::string key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
  BlockCipher::AES aes(key);
  std::cout << aes.Encrypt(input).ToHex() << std::endl;
  return 0;
}