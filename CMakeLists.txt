cmake_minimum_required(VERSION 3.2)
project(block-cipher)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

link_directories(${CMAKE_SOURCE_DIR}/lib/byte_utils/lib)

add_executable(${CMAKE_PROJECT_NAME}
  main.cpp
  src/aes.cpp
)
target_include_directories(
  ${CMAKE_PROJECT_NAME} PRIVATE 
  ${CMAKE_SOURCE_DIR}/lib/byte_utils/lib/include
)
target_link_libraries(${CMAKE_PROJECT_NAME} _byte_utils)