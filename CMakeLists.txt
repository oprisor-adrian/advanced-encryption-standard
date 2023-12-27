#[[
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
]]
cmake_minimum_required(VERSION 3.2)
project(aes)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(ByteUtils REQUIRED)

add_library(_${CMAKE_PROJECT_NAME}
  src/aes.cpp
)

add_executable(${CMAKE_PROJECT_NAME}
  main.cpp
  src/aes.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ByteUtils)

enable_testing()
add_subdirectory(test/)