cmake_minimum_required(VERSION 3.5)

MACRO(MACRO_ENSURE_OUT_OF_SOURCE_BUILD MSG)
     STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}"
     "${CMAKE_BINARY_DIR}" insource)
     GET_FILENAME_COMPONENT(PARENTDIR ${CMAKE_SOURCE_DIR} PATH)
     STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}"
     "${PARENTDIR}" insourcesubdir)
    IF(insource OR insourcesubdir)
        MESSAGE(FATAL_ERROR "${MSG}")
    ENDIF(insource OR insourcesubdir)
ENDMACRO(MACRO_ENSURE_OUT_OF_SOURCE_BUILD)

MACRO_ENSURE_OUT_OF_SOURCE_BUILD(
    "${CMAKE_PROJECT_NAME} requires an out of source build."
)

# set the project name and version
project(Platformer VERSION 1.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Catch2 REQUIRED)

set(SRC_FILES "src/guy.cpp" "src/guy_manager.cpp")
set(TEST_FILES "tests/catch_main.cpp" "tests/test_guy.cpp")

set(WINDOW_FILES "src/window.cpp")

#set(HEADER_FILES platformer.hpp)
# Build code
#add_executable(platformer "platformer.cpp" ${HEADER_FILES})
#target_include_directories(platformer PRIVATE ".")

# Build catch2 test
add_executable(test_guy ${SRC_FILES} ${TEST_FILES})
target_link_libraries(test_guy Catch2::Catch2)

# Build platformer
add_executable(platformer "src/main.cpp" ${SRC_FILES} ${WINDOW_FILES})
target_link_libraries(platformer ${SDL2_LIBRARIES})

# Build guy and guy manager
add_executable(guy "src/guy_main.cpp" ${SRC_FILES} )

# Will add targets for running tests, valgrind, etc.
#option(PARSE_CATCH_TESTS_VERBOSE ON)
include(CTest)
#include(Catch)
#catch_discover_tests(test_platformer)

include(ParseAndAddCatchTests)
ParseAndAddCatchTests(test_guy)
