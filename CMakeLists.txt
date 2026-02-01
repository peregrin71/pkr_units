cmake_minimum_required(VERSION 3.20)
project(si_units CXX)

# Include clang-format setup
include(${CMAKE_CURRENT_SOURCE_DIR}/build/clang-format.cmake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Coverage (clang + Linux + Debug only)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
        add_link_options(-fprofile-instr-generate -fcoverage-mapping)
    else()
        message(WARNING "ENABLE_COVERAGE is only supported for Clang Debug builds")
    endif()
endif()

# Treat warnings as errors
if(MSVC)
    add_compile_options(/WX /permissive-)
else()
    add_compile_options(-Werror)
endif()

# Enable testing
enable_testing()

# Add SDK include directory to global include paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sdk/include)

find_package(GTest REQUIRED CONFIG)

# Add the tests subdirectory
add_subdirectory(tests)

# Run clang-format on SDK and tests directories (local builds only, not in CI)
if(NOT DEFINED ENV{GITHUB_ACTIONS} AND NOT DEFINED ENV{CI})
    clang_format(${CMAKE_CURRENT_SOURCE_DIR}/sdk/include)
    clang_format(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

