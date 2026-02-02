cmake_minimum_required(VERSION 3.20)
project(si_units CXX)

# Include clang-format setup
include(${CMAKE_CURRENT_SOURCE_DIR}/build/clang-format.cmake)

# Common compiler-agnostic settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure C++ language is enabled
enable_language(CXX)

# if (NOT CMAKE_CXX_COMPILER_ID)
#     message (STATUS "===== COMPILER DETECTION DEBUG =====")
#     message (STATUS "CMAKE_CXX_COMPILER_ID: '${CMAKE_CXX_COMPILER_ID}'")
#     message (STATUS "CMAKE_CXX_COMPILER: '${CMAKE_CXX_COMPILER}'")
#     message (STATUS "CMAKE_CXX_COMPILER_LOADED: '${CMAKE_CXX_COMPILER_LOADED}'")
#     message (STATUS "CMAKE_CXX_COMPILER_WORKS: '${CMAKE_CXX_COMPILER_WORKS}'")
#     message (STATUS "CXX enabled: '${CMAKE_CXX_COMPILER_LOADED}'")
#     message (STATUS "CMAKE_CROSSCOMPILING: '${CMAKE_CROSSCOMPILING}'")
#     message (STATUS "CMAKE_SYSTEM_NAME: '${CMAKE_SYSTEM_NAME}'")
#     message (STATUS "WIN32 : '${WIN32}'")
#     message (STATUS "CONAN_CMAKE_SYSROOT: '${CONAN_CMAKE_SYSROOT}'")
#     message (STATUS "CONAN_CMAKE_FIND_ROOT_PATH: '${CONAN_CMAKE_FIND_ROOT_PATH}'")
#     message (STATUS "CMAKE_SYSROOT: '${CMAKE_SYSROOT}'")
#     message (STATUS "CMAKE_FIND_ROOT_PATH: '${CMAKE_FIND_ROOT_PATH}'")
#     message (STATUS "====================================")
#     message (FATAL_ERROR "Compiler ID not set - see debug info above")
# endif()

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

# Add the tests subdirectory
add_subdirectory(tests)

# Run clang-format on SDK and tests directories (local builds only, not in CI)
if(NOT DEFINED ENV{GITHUB_ACTIONS} AND NOT DEFINED ENV{CI})
    clang_format(${CMAKE_CURRENT_SOURCE_DIR}/sdk/include)
    clang_format(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
