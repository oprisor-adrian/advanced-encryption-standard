cmake_minimum_required(VERSION 3.22)
project(byte_utils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(lib_${CMAKE_PROJECT_NAME}
  src/byte.cpp
  src/word.cpp
  src/byte_vector.cpp
)

add_executable(${CMAKE_PROJECT_NAME}
  byte_utils.cpp
  src/byte.cpp
  src/word.cpp
  src/byte_vector.cpp
)

enable_testing()
add_subdirectory(test/)