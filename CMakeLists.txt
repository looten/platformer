cmake_minimum_required(VERSION 3.5)

# set the project name and version
project(Platformer VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Catch2 REQUIRED)

set(SRC_FILES "src/platformer.cpp")
set(TEST_FILES "tests/catch_main.cpp" "tests/test_platformer.cpp")

#set(HEADER_FILES platformer.hpp)
# Build code
#add_executable(platformer "platformer.cpp" ${HEADER_FILES})
#target_include_directories(platformer PRIVATE ".")

# Build catch2 test
add_executable(test_platformer ${SRC_FILES} ${TEST_FILES})
target_link_libraries(test_platformer Catch2::Catch2)

# Will add targets for running tests, valgrind, etc.
include(CTest)
include(Catch)
catch_discover_tests(test_platformer)
