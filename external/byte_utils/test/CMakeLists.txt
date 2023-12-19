find_package(GTest REQUIRED)
include(GoogleTest)
add_executable(${CMAKE_PROJECT_NAME}_test
  test_byte.cpp
  test_word.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME}_test
  GTest::gtest_main
  lib_${CMAKE_PROJECT_NAME}  
)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_test)