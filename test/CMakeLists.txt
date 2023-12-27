#[[
  Copyright (C) 2023 Oprișor Adrian-Ilie
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
  
  Contact: contact@dev-adrian.com
]]
find_package(GTest REQUIRED)
include(GoogleTest)
add_executable(${CMAKE_PROJECT_NAME}_test
  test_aes.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME}_test
  GTest::gtest_main
  _${CMAKE_PROJECT_NAME}
  ByteUtils
)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_test)