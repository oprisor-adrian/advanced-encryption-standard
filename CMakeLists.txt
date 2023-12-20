cmake_minimum_required(VERSION 3.2)
project(block-cipher)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

link_directories(${PROJECT_SOURCE_DIR}/external/byte_utils/lib)
include_directories(${PROJECT_SOURCE_DIR}/external/byte_utils/include)

add_executable(${CMAKE_PROJECT_NAME}
  main.cpp
  src/aes.cpp
  src/aes_256.cpp
  src/byte_vector.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} _byte_utils)

add_library(${CMAKE_PROJECT_NAME}_lib
  src/aes.cpp
  src/aes_256.cpp
  src/byte_vector.cpp
)

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/test/)