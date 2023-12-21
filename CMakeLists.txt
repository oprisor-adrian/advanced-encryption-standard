cmake_minimum_required(VERSION 3.2)
project(block-cipher)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

link_directories(${PROJECT_SOURCE_DIR}/external/byte_utils/lib)
include_directories(${PROJECT_SOURCE_DIR}/external/byte_utils/lib/include)

add_executable(${CMAKE_PROJECT_NAME}
  main.cpp
  src/aes.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME} _byte_utils)