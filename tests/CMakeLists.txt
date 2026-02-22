cmake_minimum_required(VERSION 3.20)

# Add SDK include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)

# Required to run the umbrella generator script
find_package(Python3 COMPONENTS Interpreter REQUIRED)

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
  computer_science/test_bits_bytes.cpp
  computer_science/test_flops.cpp
  computer_science/test_neural_ops.cpp
  computer_science/test_rates.cpp
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
  electrical/test_complex_impedance.cpp
  electrical/test_complex_formatting.cpp
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
  # magnetic/test_magnetic_flux_density.cpp
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
  storage/test_matrix_storage_policies.cpp
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

# ---------------------------------------------------------------------------
# Compile-fail tests (verify concise static_assert diagnostics for invalid use)
# These run the compiler in syntax-check mode and grep for the expected message.
# Only enabled on Unix-like environments where /bin/sh is available.
# ---------------------------------------------------------------------------
if(UNIX)
  add_test(NAME cf_operator_plus COMMAND /bin/sh -c "${CMAKE_CXX_COMPILER} -fsyntax-only -std=c++${CMAKE_CXX_STANDARD} -I${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/tests/compile_fail/cf_operator_plus.cpp 2>&1 | grep -F \"invalid operands to operator+ : operands must have the same dimensions\"")
  add_test(NAME cf_operator_minus COMMAND /bin/sh -c "${CMAKE_CXX_COMPILER} -fsyntax-only -std=c++${CMAKE_CXX_STANDARD} -I${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/tests/compile_fail/cf_operator_minus.cpp 2>&1 | grep -F \"invalid operands to operator- : operands must have the same dimensions\"")
  add_test(NAME cf_sqrt COMMAND /bin/sh -c "${CMAKE_CXX_COMPILER} -fsyntax-only -std=c++${CMAKE_CXX_STANDARD} -I${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/tests/compile_fail/cf_sqrt.cpp 2>&1 | grep -F \"sqrt() requires unit dimensions that are even and non-negative\"")
  add_test(NAME cf_sin COMMAND /bin/sh -c "${CMAKE_CXX_COMPILER} -fsyntax-only -std=c++${CMAKE_CXX_STANDARD} -I${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/tests/compile_fail/cf_sin.cpp 2>&1 | grep -F \"sin() requires an angle unit\"")
  add_test(NAME cf_unit_t_ctor COMMAND /bin/sh -c "${CMAKE_CXX_COMPILER} -fsyntax-only -std=c++${CMAKE_CXX_STANDARD} -I${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/tests/compile_fail/cf_unit_t_ctor.cpp 2>&1 | grep -F \"unit_t: cannot construct from unit with different dimensions\"")
  add_test(NAME cf_meter_ctor COMMAND /bin/sh -c "${CMAKE_CXX_COMPILER} -fsyntax-only -std=c++${CMAKE_CXX_STANDARD} -I${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/tests/compile_fail/cf_meter_ctor.cpp 2>&1 | grep -F \"meter_t: expected a length unit\"")
endif()

# Option to generate a single preprocessed header from all SDK headers.
option(GENERATE_SINGLE_HEADER "Generate a single preprocessed header" OFF)

# Only enable generation on Linux + Clang to match local linux-clang profile.
if(GENERATE_SINGLE_HEADER AND UNIX AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message(STATUS "GENERATE_SINGLE_HEADER is ON: adding custom target to precompute single header")

  # Output header in the build tree
  set(SINGLE_HEADER_OUT ${CMAKE_BINARY_DIR}/compiler_explorer/pkr_units/single_header_test.h)
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/compiler_explorer/pkr_units)

  # Collect all SDK headers as dependencies so we regenerate when any header changes
  file(GLOB_RECURSE PKR_UNITS_HEADERS
    ${CMAKE_SOURCE_DIR}/sdk/include/pkr_units/*.h
  )

  # Umbrella generator script will write tests/tools/_all_sdk_headers.h
  set(UMBRELLA_OUT ${CMAKE_SOURCE_DIR}/tests/tools/_all_sdk_headers.h)
  add_custom_command(
    OUTPUT ${UMBRELLA_OUT}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/generate_tests_umbrella.py --out ${UMBRELLA_OUT}
    DEPENDS ${PKR_UNITS_HEADERS} ${CMAKE_SOURCE_DIR}/tools/generate_tests_umbrella.py
    COMMENT "Generating umbrella header ${UMBRELLA_OUT}"
    VERBATIM
  )

  add_custom_target(generate_umbrella DEPENDS ${UMBRELLA_OUT})

  # Raw preprocessed output (keeps #line markers so we can determine origin files)
  set(SINGLE_HEADER_RAW ${CMAKE_BINARY_DIR}/compiler_explorer/pkr_units/single_header_raw.h)
  add_custom_command(
    OUTPUT ${SINGLE_HEADER_RAW}
    # Ensure output directory
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/compiler_explorer/pkr_units
    COMMAND /bin/sh -lc "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -E -x c++ -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_SOURCE_DIR}/tests/tools/_all_sdk_tu.cpp -I ${CMAKE_SOURCE_DIR}/sdk/include -o ${SINGLE_HEADER_RAW}"
    DEPENDS ${PKR_UNITS_HEADERS} ${CMAKE_SOURCE_DIR}/tests/tools/_all_sdk_tu.cpp ${UMBRELLA_OUT}
    COMMENT "Generating raw preprocessed header: ${SINGLE_HEADER_RAW}"
    VERBATIM
  )

  # Postprocess raw preprocessed output into cleaned CE header in source tree
  set(CE_HEADER ${CMAKE_SOURCE_DIR}/ce/pkr_units.h)
  add_custom_command(
    OUTPUT ${CE_HEADER}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/postprocess_preprocessed.py --input ${SINGLE_HEADER_RAW} --output ${CE_HEADER} --project-root ${CMAKE_SOURCE_DIR}/sdk/include/pkr_units
    DEPENDS ${SINGLE_HEADER_RAW} ${CMAKE_SOURCE_DIR}/tools/postprocess_preprocessed.py
    COMMENT "Postprocessing raw header into cleaned ${CE_HEADER}"
    VERBATIM
  )

  add_custom_target(generate_ce_header DEPENDS ${CE_HEADER})
  add_dependencies(generate_ce_header generate_umbrella)
  add_dependencies(generate_ce_header generate_single_header)

  add_custom_target(generate_single_header DEPENDS ${SINGLE_HEADER_RAW})
  add_dependencies(generate_single_header generate_umbrella)
  add_dependencies(si_units_test generate_single_header generate_ce_header)
endif()


