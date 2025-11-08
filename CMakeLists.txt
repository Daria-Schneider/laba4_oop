cmake_minimum_required(VERSION 3.15)
project(laba4_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(laba4_oop
    src/main.cpp
)

add_executable(laba4_tests
    tests/test_figures.cpp
    tests/main_test.cpp
)

target_include_directories(laba4_oop PRIVATE include)
target_include_directories(laba4_tests PRIVATE include)

target_link_libraries(laba4_tests PRIVATE gtest_main)

enable_testing()
add_test(NAME Lab4Tests COMMAND laba4_tests)

target_compile_features(laba4_oop PRIVATE cxx_std_20)
target_compile_features(laba4_tests PRIVATE cxx_std_20)