find_package(GTest REQUIRED)
include(GoogleTest)
add_executable(${CMAKE_PROJECT_NAME}_test
  test_aes.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME}_test
  GTest::gtest_main
  _${CMAKE_PROJECT_NAME}
  _byte_utils
)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_test)