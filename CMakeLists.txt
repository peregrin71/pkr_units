cmake_minimum_required(VERSION 3.20)
project(si_units CXX)

# Include clang-format and clang-tidy setup
include(${CMAKE_CURRENT_SOURCE_DIR}/build/clang-format.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/build/clang-tidy.cmake)

# Common compiler-agnostic settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure C++ language is enabled
enable_language(CXX)

message (STATUS "Setting compiler settings for compiler : ${CMAKE_CXX_COMPILER_ID}")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/clang_settings.cmake)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/msvc_settings.cmake)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/gcc_settings.cmake)
else()
    message (FATAL_ERROR "Unsupported compiler: '${CMAKE_CXX_COMPILER_ID}'")
endif()

# Enable testing
enable_testing()

# Add SDK include directory to global include paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sdk/include)

find_package(GTest REQUIRED CONFIG)

# Run clang-format on SDK and tests directories (local builds only, not in CI)
if(NOT DEFINED ENV{GITHUB_ACTIONS} AND NOT DEFINED ENV{CI})
    clang_format(${CMAKE_CURRENT_SOURCE_DIR}/sdk/include)
    clang_format(${CMAKE_CURRENT_SOURCE_DIR}/tests)
    #clang_tidy(${CMAKE_CURRENT_SOURCE_DIR}/sdk/include)
    #clang_tidy(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

# Add the tests subdirectory
add_subdirectory(tests)
