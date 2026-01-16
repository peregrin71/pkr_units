cmake_minimum_required(VERSION 3.20)

# Add SDK include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)

# Collect all test source files
set(TEST_SOURCES
  main.cpp
  test_si_length.cpp
  test_si_mass.cpp
  test_si_time.cpp
  test_si_current.cpp
  test_si_temperature.cpp
  test_si_amount.cpp
  test_si_intensity.cpp
  test_arithmetic_optimizations.cpp
  # test_si_length_cast.cpp  (casting tests - will enable later)
  # test_si_length_imperial.cpp
  # test_si_length_astronomical.cpp
  # test_si_length_formatting.cpp
  # test_si_multi_cast.cpp
)

# Create the test executable
add_executable(si_units_test ${TEST_SOURCES})

# Link against Google Test (provided by Conan)
target_link_libraries(si_units_test PRIVATE GTest::gtest)

# Register the test executable as a test that CTest will run
add_test(NAME si_units_test COMMAND si_units_test)

