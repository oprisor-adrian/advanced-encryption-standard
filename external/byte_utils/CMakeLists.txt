cmake_minimum_required(VERSION 3.22)
project(byte_utils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_library(_${CMAKE_PROJECT_NAME}
  src/byte.cpp
  src/word.cpp
  src/byte_vector.cpp
)

enable_testing()
add_subdirectory(test/)