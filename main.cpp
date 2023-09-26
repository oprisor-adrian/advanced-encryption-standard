#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "include/aes_256.h"

int main() {
  std::string input = "00112233445566778899aabbccddeeff";
  std::string key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
  BlockCipher::AES256 aes256({input}, {key});
  std::cout << aes256.Encrypt() << std::endl;
  return 0;
}