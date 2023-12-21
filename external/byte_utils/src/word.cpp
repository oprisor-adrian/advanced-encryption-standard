#include "word.h"

#include <sstream>
#include <stdexcept>

namespace ByteUtils {

Word::Word(const std::string& data) {
  std::size_t hex_index = 0;
  for (auto it = word_.begin(); it != word_.end(); ++it) {
    *it = Byte(data.substr(hex_index, 2), 16);
    hex_index += 2;
  }
}

Word::Word(const std::array<Byte, 4>& word): word_(word) {}

std::ostream& operator<<(std::ostream& stream, const Word& data) {
  for (const auto& byte : data.GetWord()) {
    stream << byte;
  }
  return stream;
}

Word Word::operator^(const Word& word) const {
  std::array<Byte, 4> result;
  for (std::size_t index = 0; index < 4; index++) {
    result[index] = word_[index] ^ word.GetWord()[index];
  }
  return result;
}

Word Word::operator^(const Byte& byte) const {
  std::array<Byte, 4> result;
  for (std::size_t index = 0; index < 4 ; index++) {
    result[index] = word_[index] ^ byte;
  }
  return result;
}

Byte Word::operator[](const std::size_t pos) const {
  if (pos >= 4 || pos < 0) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  return word_[pos];
}

Byte& Word::operator[](const std::size_t pos) {
  if (pos >= 4 || pos < 0) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  return word_[pos];
}

std::string Word::ToHex() const {
  std::stringstream stream;
  for (const auto& byte : word_) {
    stream << byte.ToHex();
  }
  return stream.str();
}

}  // namespace ByteUtils