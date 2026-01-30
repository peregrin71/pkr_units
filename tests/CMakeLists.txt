cmake_minimum_required(VERSION 3.20)

# Add SDK include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)

# Collect all test source files
set(TEST_SOURCES
  main.cpp
  
  # Base unit tests
  length/test_si_length.cpp
  length/test_si_length_operators.cpp
  length/test_si_length_cast.cpp
  length/test_si_length_formatting.cpp
  length/test_si_length_literals.cpp
  length/test_si_length_astronomical.cpp
  length/test_si_length_imperial.cpp
  length/test_si_length_non_si_units.cpp
  mass/test_si_mass.cpp
  mass/test_si_mass_operators.cpp
  mass/test_si_mass_formatting.cpp
  time/test_si_time.cpp
  time/test_si_time_operators.cpp
  time/test_si_time_formatting.cpp
  time/test_chrono_cast.cpp
  current/test_si_current.cpp
  current/test_si_current_operators.cpp
  current/test_si_current_formatting.cpp
  temperature/test_si_temperature.cpp
  temperature/test_si_temperature_operators.cpp
  temperature/test_si_temperature_formatting.cpp
  temperature/test_temperature_cast.cpp
  amount/test_si_amount.cpp
  amount/test_si_amount_operators.cpp
  amount/test_si_amount_formatting.cpp
  intensity/test_si_intensity.cpp
  intensity/test_si_intensity_operators.cpp
  intensity/test_si_intensity_formatting.cpp
  angle/test_si_angle_formatting.cpp
  angle/test_si_angle.cpp
  astronomical/test_astronomical_angle_formatting.cpp
  dimensionless/test_dimensionless_cast.cpp
  dimensionless/test_dimensionless_formatting.cpp

  velocity/test_si_velocity.cpp
  velocity/test_imperial_velocity.cpp

  # Derived unit tests
  acceleration/test_acceleration.cpp
  acceleration/test_acceleration_operators.cpp
  acceleration/test_acceleration_formatting.cpp
  acceleration/test_acceleration_cast.cpp

  force/test_force.cpp
  force/test_force_operators.cpp
  force/test_force_formatting.cpp
  force/test_force_cast.cpp

  energy/test_energy.cpp
  energy/test_energy_operators.cpp
  energy/test_energy_formatting.cpp
  energy/test_energy_cast.cpp
  thermal/test_specific_heat_capacity.cpp
  thermal/test_thermal_conductivity.cpp
  viscosity/test_viscosity.cpp

  concentration/test_concentration.cpp
  concentration/test_concentration_operators.cpp
  concentration/test_concentration_cast.cpp
  concentration/test_concentration_formatting.cpp
  area/test_si_area_formatting.cpp
  volume/test_si_volume_formatting.cpp

  pressure/test_si_pressure_formatting.cpp
  pressure/test_imperial_pressure_formatting.cpp
  power/test_si_power_formatting.cpp
  power/test_imperial_power_formatting.cpp
  electrical/test_si_resistance_formatting.cpp
  electrical/test_si_electrical_formatting.cpp
  magnetic/test_magnetic_flux_density.cpp
  cgs/test_cgs_units.cpp

  # Multi-unit cast tests
  multi_cast/test_multi_unit_cast.cpp
  
  # Math tests
  math/test_arithmetic_optimizations.cpp
  math/test_math_functions.cpp
  
  # Numerical tests
  numerical/test_three_body_problem.cpp
  
  # Measurement tests
  measurements/test_measurement_linear.cpp
  measurements/test_measurement_rss.cpp
  measurements/test_measurement_edge_cases.cpp
  
  # Dimensional analysis tests
  test_dimensional_analysis.cpp
  
  # Constants tests
  test_constants.cpp
  test_constants_comprehensive.cpp
  test_spaceship_operator.cpp
  
  # Formatting tests
  test_formatting.cpp
  
  # Compile-time safety and dimensional error documentation
  test_dimensional_safety.cpp
  
)

# Create the test executable
add_executable(si_units_test ${TEST_SOURCES})

# Link against Google Test (provided by Conan)
target_link_libraries(si_units_test PRIVATE GTest::gtest GTest::gtest_main)

# Register the test executable as a test that CTest will run
add_test(NAME si_units_test COMMAND si_units_test --gtest_filter=MultiCastTest.*)
#add_test(NAME si_units_test COMMAND si_units_test)


