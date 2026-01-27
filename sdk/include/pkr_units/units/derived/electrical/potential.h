#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Electric potential dimension
inline constexpr dimension_t electric_potential_dimension{2, 1, -3, -1, 0, 0, 0, 0};

// Strong type for volt (SI base unit)
struct volt final : public details::unit_t<double, std::ratio<1, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_potential_dimension>;
    using _base::_base;
    const std::string_view name{"volt"};
    const std::string_view symbol{"V"};
    const std::wstring_view w_symbol{L"V"};
    const std::u8string_view u8_symbol{u8"V"};
};

// Strong type for kilovolt
struct kilovolt final : public details::unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>;
    using _base::_base;
    const std::string_view name{"kilovolt"};
    const std::string_view symbol{"kV"};
    const std::wstring_view w_symbol{L"kV"};
    const std::u8string_view u8_symbol{u8"kV"};
};

// Strong type for megavolt
struct megavolt final : public details::unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>;
    using _base::_base;
    const std::string_view name{"megavolt"};
    const std::string_view symbol{"MV"};
    const std::wstring_view w_symbol{L"MV"};
    const std::u8string_view u8_symbol{u8"MV"};
};

// Strong type for millivolt
struct millivolt final : public details::unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>;
    using _base::_base;
    const std::string_view name{"millivolt"};
    const std::string_view symbol{"mV"};
    const std::wstring_view w_symbol{L"mV"};
    const std::u8string_view u8_symbol{u8"mV"};
};

// Strong type for microvolt
struct microvolt final : public details::unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>;
    using _base::_base;
    const std::string_view name{"microvolt"};
    const std::string_view symbol{"µV"};
    const std::wstring_view w_symbol{L"µV"};
    const std::u8string_view u8_symbol{u8"µV"};
};

} // namespace PKR_UNITS_NAMESPACE
