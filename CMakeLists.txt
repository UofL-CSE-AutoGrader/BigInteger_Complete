cmake_minimum_required(VERSION 3.14)
project(BigInteger VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Build the main Integer library
add_library(integer_lib
    src/Integer.cpp
    src/Integer_Arithmetic.cpp
    src/Integer_Utilities.cpp
    src/Integer_Bitwise.cpp
    src/Integer_Comparison.cpp
    src/Integer_Modular.cpp
)

# Public include path for consumers
target_include_directories(integer_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Create a namespace alias target
add_library(BigInteger::BigInteger ALIAS integer_lib)

# Build the executable for manual testing (optional)
add_executable(integer_main src/main.cpp)
target_link_libraries(integer_main PRIVATE integer_lib)

# Unit tests
file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(integer_tests ${TEST_SOURCES})
target_link_libraries(integer_tests PRIVATE gtest_main integer_lib)
include(GoogleTest)
gtest_discover_tests(integer_tests)

