enable_testing()
find_package(GTest REQUIRED)
add_executable(${CMAKE_PROJECT_NAME}_byte_vector_test
  test_byte_vector.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME}_byte_vector_test
  GTest::gtest_main
  ${CMAKE_PROJECT_NAME}_lib
)
include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_byte_vector_test)