cmake_minimum_required(VERSION 3.22)
project(byte_utils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

add_library(_${CMAKE_PROJECT_NAME} SHARED
  src/byte.cpp
  src/word.cpp
  src/byte_vector.cpp
)

install(
  TARGETS _${CMAKE_PROJECT_NAME} 
  LIBRARY DESTINATION lib
)
install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/include/
  DESTINATION lib/include
  FILES_MATCHING PATTERN "*.h"
)

enable_testing()
add_subdirectory(test/)