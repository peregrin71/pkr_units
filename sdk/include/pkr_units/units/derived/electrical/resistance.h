#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Electric resistance dimension
inline constexpr dimension_t electric_resistance_dimension{2, 1, -3, -2, 0, 0, 0, 0};

// Strong type for ohm (SI base unit)
struct ohm final : public details::unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ohm"};
    static constexpr std::string_view symbol{"ohm"};
    static constexpr std::wstring_view w_symbol{L"Ω"};
    static constexpr std::u8string_view u8_symbol{u8"Ω"};
};

// Strong type for kilohm
struct kilohm final : public details::unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilohm"};
    static constexpr std::string_view symbol{"kohm"};
    static constexpr std::wstring_view w_symbol{L"kΩ"};
    static constexpr std::u8string_view u8_symbol{u8"kΩ"};
};

// Strong type for megohm
struct megohm final : public details::unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megohm"};
    static constexpr std::string_view symbol{"Mohm"};
    static constexpr std::wstring_view w_symbol{L"MΩ"};
    static constexpr std::u8string_view u8_symbol{u8"MΩ"};
};

// Strong type for gigohm
struct gigohm final : public details::unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigohm"};
    static constexpr std::string_view symbol{"Gohm"};
    static constexpr std::wstring_view w_symbol{L"GΩ"};
    static constexpr std::u8string_view u8_symbol{u8"GΩ"};
};

// Strong type for milliohm
struct milliohm final : public details::unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliohm"};
    static constexpr std::string_view symbol{"mohm"};
    static constexpr std::wstring_view w_symbol{L"mΩ"};
    static constexpr std::u8string_view u8_symbol{u8"mΩ"};
};

// Strong type for microohm
struct microohm final : public details::unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microohm"};
    static constexpr std::string_view symbol{"uohm"};
    static constexpr std::wstring_view w_symbol{L"µΩ"};
    static constexpr std::u8string_view u8_symbol{u8"µΩ"};
};

} // PKR_UNITS_NAMESPACE








