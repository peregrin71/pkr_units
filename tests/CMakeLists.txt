cmake_minimum_required(VERSION 3.20)

# Add SDK include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)

# Collect all test source files
set(TEST_SOURCES
  main.cpp
  
  # Base unit tests
  length/test_si_length.cpp
  length/test_si_length_operators.cpp
  # mass/test_si_mass.cpp
  # time/test_si_time.cpp
  # current/test_si_current.cpp
  # temperature/test_si_temperature.cpp
  # amount/test_si_amount.cpp
  # intensity/test_si_intensity.cpp
  
  # Derived unit tests
  # velocity/test_si_velocity.cpp
  
  # General/optimization tests
  # general/test_arithmetic_optimizations.cpp
)

# Create the test executable
add_executable(si_units_test ${TEST_SOURCES})

# Link against Google Test (provided by Conan)
target_link_libraries(si_units_test PRIVATE GTest::gtest)

# Register the test executable as a test that CTest will run
add_test(NAME si_units_test COMMAND si_units_test)

