cmake_minimum_required(VERSION 3.20)
project(si_units CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

find_package(GTest REQUIRED)

# Add the tests subdirectory
add_subdirectory(tests)

