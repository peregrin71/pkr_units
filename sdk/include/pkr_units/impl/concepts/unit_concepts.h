#pragma once
#include <concepts>
#include <complex>
#include <type_traits>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Concept to check if a unit type represents an angle (dimensionless in angle sense)
template <typename UnitT>
concept is_angle_unit_c = requires { typename UnitT::dimension; } && UnitT::dimension::value.angle == 1 && UnitT::dimension::value.length == 0 &&
                          UnitT::dimension::value.mass == 0 && UnitT::dimension::value.time == 0 && UnitT::dimension::value.current == 0 &&
                          UnitT::dimension::value.temperature == 0 && UnitT::dimension::value.amount == 0 && UnitT::dimension::value.intensity == 0;

// Concept for scalar-like numeric types accepted by scalar operators and APIs
// Accepts: float, double (complex types excluded for now)
// Explicitly excludes boolean and integer types
template <typename ScalarT>
concept scalar_value_c = std::same_as<std::remove_cvref_t<ScalarT>, float> || std::same_as<std::remove_cvref_t<ScalarT>, double>;

static_assert(scalar_value_c<float>);
static_assert(scalar_value_c<double>);
static_assert(!scalar_value_c<bool>);

// Concept for any direct unit_t type (not derived)
template <typename T>
concept is_base_unit_t_c = std::same_as<
    T,
    details::unit_t<typename details::is_pkr_unit<T>::value_type, typename details::is_pkr_unit<T>::ratio_type, details::is_pkr_unit<T>::value_dimension>>;

// Concept for derived pkr_unit types (those with a _base member inheriting from it)
template <typename T>
concept is_derived_pkr_unit_c = requires { typename T::_base; } && std::is_base_of_v<typename T::_base, T>;

// Concept for direct pkr_unit_t types only (not derived)
template <typename T>
concept is_base_pkr_unit_c = details::is_pkr_unit<T>::value && !is_derived_pkr_unit_c<T>;

// Concept for ANY pkr_unit type (direct or derived, but NOT measurement-wrapped)
template <typename T>
concept is_pkr_unit_c = is_base_pkr_unit_c<T> || is_derived_pkr_unit_c<T>;

// Concept to check if a dimension_t allows taking square root (all exponents even and non-negative)
template <dimension_t Dim>
concept pkr_unit_can_take_square_root_c = Dim.length >= 0 && Dim.length % 2 == 0 && Dim.mass >= 0 && Dim.mass % 2 == 0 && Dim.time >= 0 && Dim.time % 2 == 0 &&
                                          Dim.current >= 0 && Dim.current % 2 == 0 && Dim.temperature >= 0 && Dim.temperature % 2 == 0 && Dim.amount >= 0 &&
                                          Dim.amount % 2 == 0 && Dim.intensity >= 0 && Dim.intensity % 2 == 0 && Dim.angle >= 0 && Dim.angle % 2 == 0;

} // namespace PKR_UNITS_NAMESPACE
