#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "include/aes_256.h"

int main() {
  std::string input = "00112233445566778899aabbccddeeff";
  std::string key = "60 3d eb 10 15 ca 71 be 2b 73 ae f0 85 7d 77 81 \
                     1f 35 2c 07 3b 61 08 d7 2d 98 10 a3 09 14 df f4";
  BlockCipher::AES256 aes256({input}, {key});
  return 0;
}