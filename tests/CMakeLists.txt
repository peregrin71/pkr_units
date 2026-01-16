cmake_minimum_required(VERSION 3.20)

# Add SDK include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)

# Collect all test source files
file(GLOB TEST_SOURCES "*.cpp")

# Create the test executable
add_executable(si_units_test ${TEST_SOURCES})

# Link against Google Test (provided by Conan)
target_link_libraries(si_units_test PRIVATE GTest::gtest GTest::gtest_main)

# Add the test to CMake's test suite
add_test(NAME si_units_test COMMAND si_units_test)
