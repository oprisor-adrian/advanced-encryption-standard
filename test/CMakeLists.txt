enable_testing()
find_package(GTest REQUIRED)
add_executable(${CMAKE_PROJECT_NAME}_block_cipher
  test_byte_vector.cpp
  test_aes_256.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME}_block_cipher
  GTest::gtest_main
  ${CMAKE_PROJECT_NAME}_lib
)
include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_block_cipher)