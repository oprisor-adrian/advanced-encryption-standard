#ifndef BYTE_UTILS_BYTE_VECTOR_H_
#define BYTE_UTILS_BYTE_VECTOR_H_

#include <string>
#include <vector>

#include "byte.h"

namespace ByteUtils {

class ByteVector{
  public:
    ByteVector(const std::string& hex_string);
    ByteVector(const std::vector<Byte> byte_vector);
  private:
    std::vector<Byte> bytes_;
};

}  // namespace ByteUtils

#endif  // BYTE_UTILS_BYTE_VECTOR_H_