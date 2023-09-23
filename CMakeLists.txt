cmake_minimum_required(VERSION 3.2)
project(block-cipher)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(PROJECT_SOURCES
  main.cpp
  src/aes_256.cpp
  src/byte_vector.cpp
)
add_executable(${CMAKE_PROJECT_NAME}
  ${PROJECT_SOURCES}
)
add_library(${CMAKE_PROJECT_NAME}_lib
  ${PROJECT_SOURCES}
)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/)