#include <iostream>

#include "include/byte_vector.h"

int main() {
  BlockCipher::ByteVector bv("000102030405060708090a0b0c0d0e0f");
  BlockCipher::ByteVector bv1 = bv[{0, 3}];
  std::cout << bv1 << std::endl;
  return 0;
}