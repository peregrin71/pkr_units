cmake_minimum_required(VERSION 3.20)

# Add SDK include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)

# Collect all test source files
set(TEST_SOURCES
  main.cpp
  
  acceleration/test_acceleration_cast.cpp
  acceleration/test_acceleration_formatting.cpp
  acceleration/test_acceleration_operators.cpp
  acceleration/test_acceleration.cpp
  amount/test_si_amount_formatting.cpp
  amount/test_si_amount_operators.cpp
  amount/test_si_amount.cpp
  angle/test_si_angle_formatting.cpp
  angle/test_si_angle.cpp
  area/test_si_area_formatting.cpp
  astronomical/test_astronomical_angle_formatting.cpp
  cgs/test_cgs_units.cpp
  concentration/test_concentration_cast.cpp
  concentration/test_concentration_formatting.cpp
  concentration/test_concentration_operators.cpp
  concentration/test_concentration.cpp
  current/test_si_current_formatting.cpp
  current/test_si_current_operators.cpp
  current/test_si_current.cpp
  dimensionless/test_dimensionless_cast.cpp
  dimensionless/test_dimensionless_formatting.cpp
  electrical/test_si_electrical_formatting.cpp
  electrical/test_si_resistance_formatting.cpp
  energy/test_energy_cast.cpp
  energy/test_energy_formatting.cpp
  energy/test_energy_operators.cpp
  energy/test_energy.cpp
  force/test_force_cast.cpp
  force/test_force_formatting.cpp
  force/test_force_operators.cpp
  force/test_force.cpp
  intensity/test_si_intensity_formatting.cpp
  intensity/test_si_intensity_operators.cpp
  intensity/test_si_intensity.cpp
  length/test_si_length_astronomical.cpp
  length/test_si_length_cast.cpp
  length/test_si_length_formatting.cpp
  length/test_si_length_imperial.cpp
  length/test_si_length_literals.cpp
  length/test_si_length_non_si_units.cpp
  length/test_si_length_operators.cpp
  length/test_si_length.cpp
  magnetic/test_magnetic_flux_density.cpp
  mass/test_si_mass_formatting.cpp
  mass/test_si_mass_operators.cpp
  mass/test_si_mass.cpp
  math/test_measurement_rss_math.cpp
  math/test_unit_math_arithmetic.cpp
  math/test_unit_math_functions.cpp
  math/test_unit_math_optimizations.cpp
  math/test_vector_generic_3d.cpp
  math/test_vector_generic_4d.cpp
  math/test_vector_measurement_rss_3d.cpp
  math/test_vector_measurement_rss_4d.cpp
  math/test_vector_unit_3d.cpp
  math/test_vector_unit_4d.cpp
  measurements/test_measurement_edge_cases.cpp
  measurements/test_measurement_linear.cpp
  measurements/test_measurement_rss.cpp
  measurements/test_rk4_calculation_patterns_rss.cpp
  impl/test_unit_pow.cpp
  multi_cast/test_multi_unit_cast.cpp
  power/test_imperial_power_formatting.cpp
  power/test_si_power_formatting.cpp
  pressure/test_imperial_pressure_formatting.cpp
  pressure/test_si_pressure_formatting.cpp
  temperature/test_si_temperature_formatting.cpp
  temperature/test_si_temperature_operators.cpp
  temperature/test_si_temperature.cpp
  temperature/test_temperature_cast.cpp
  test_constants_comprehensive.cpp
  test_constants.cpp
  test_dimensional_analysis.cpp
  test_dimensional_safety.cpp
  test_formatting.cpp
  thermal/test_specific_heat_capacity.cpp
  thermal/test_thermal_conductivity.cpp
  time/test_chrono_cast.cpp
  time/test_si_time_formatting.cpp
  time/test_si_time_operators.cpp
  time/test_si_time.cpp
  velocity/test_imperial_velocity.cpp
  velocity/test_si_velocity.cpp
  viscosity/test_viscosity.cpp
  volume/test_si_volume_formatting.cpp
  integration/test_three_body_problem.cpp
)

# Create the test executable
add_executable(si_units_test ${TEST_SOURCES})

# Link against Google Test (provided by Conan)
target_link_libraries(si_units_test PRIVATE GTest::gtest GTest::gtest_main)

# Register the test executable as a test that CTest will run
# add_test(NAME si_units_test COMMAND si_units_test --gtest_filter=MultiCastTest.*)
add_test(NAME si_units_test_all COMMAND si_units_test)


