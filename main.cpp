/* 
  Copyright (C) 2023 Oprișor Adrian-Ilie
  
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
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "include/aes.h"

int main() {
  std::string input = "00112233445566778899aabbccddeeff";
  std::string key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
  Cryptography::AES aes(key);
  std::cout << aes.Encrypt(input).ToHex() << std::endl;
  return 0;
}