cmake_minimum_required(VERSION 3.20)

# Add SDK include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)

# Example executable that demonstrates usage of the header-only SDK
add_executable(pkr_units_examples main.cpp)
