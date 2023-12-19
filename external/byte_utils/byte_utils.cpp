#include <iostream>

#include "include/byte.h"

int main() {
  ByteUtils::Byte byte1("57", 16);
  ByteUtils::Byte byte2("83", 16);
  std::cout << byte1 * byte2 << std::endl;
  return 0;
}