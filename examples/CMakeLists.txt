cmake_minimum_required(VERSION 3.20)

# Add SDK include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)

# Example executable that demonstrates usage of the header-only SDK
# Includes all independent example modules
add_executable(pkr_units_examples 
    main.cpp
    ex_first_example.cpp
    ex_kinetic_energy.cpp
    ex_unit_conversion.cpp
    ex_literals.cpp
    ex_type_safety.cpp
    ex_physics_functions.cpp
    ex_derived_units.cpp
    ex_temperature.cpp
    ex_electrical_engineering.cpp
)
