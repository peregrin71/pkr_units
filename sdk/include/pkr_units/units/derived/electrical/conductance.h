#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Conductance dimension: S = A^2·s^3·kg^-1·m^-2
inline constexpr dimension_t conductance_dimension{-2, -1, 3, 2, 0, 0, 0, 0};

// Conductance units (Siemens and derived)
struct siemens_t final : public details::unit_t<double, std::ratio<1, 1>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, conductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"siemens"};
    static constexpr std::string_view symbol{"S"};
    static constexpr std::wstring_view w_symbol{L"S"};
    static constexpr std::u8string_view u8_symbol{u8"S"};
};

struct millisiemens_t final : public details::unit_t<double, std::ratio<1, 1000>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, conductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millisiemens"};
    static constexpr std::string_view symbol{"mS"};
    static constexpr std::wstring_view w_symbol{L"mS"};
    static constexpr std::u8string_view u8_symbol{u8"mS"};
};

struct microsiemens_t final : public details::unit_t<double, std::ratio<1, 1000000>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, conductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microsiemens"};
    static constexpr std::string_view symbol{"uS"};
    static constexpr std::wstring_view w_symbol{L"\u00b5S"};
    static constexpr std::u8string_view u8_symbol{u8"\u00b5S"};
};

// ============================================================================
// Most derived unit type specializations for conductance units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, conductance_dimension>
{
    using type = siemens_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, conductance_dimension>
{
    using type = millisiemens_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, conductance_dimension>
{
    using type = microsiemens_t;
};

} // namespace PKR_UNITS_NAMESPACE
