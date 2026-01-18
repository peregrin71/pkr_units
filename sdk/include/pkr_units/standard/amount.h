#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/unit.h"
#include "../impl/common/amount_def.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Strong type for mole (SI base unit)
struct mole_t final : public details::unit_t<double, std::ratio<1, 1>, amount_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"mole"};
    static constexpr std::string_view symbol{"mol"};
    static constexpr std::wstring_view w_symbol{L"mol"};
    static constexpr std::u8string_view u8_symbol{u8"mol"};
};

// Metric amount prefixes (strong types)
struct millimole_t final : public details::unit_t<double, std::milli, amount_dimension>
{
    using _base = details::unit_t<double, std::milli, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millimole"};
    static constexpr std::string_view symbol{"mmol"};
    static constexpr std::wstring_view w_symbol{L"mmol"};
    static constexpr std::u8string_view u8_symbol{u8"mmol"};
};

struct micromole_t final : public details::unit_t<double, std::micro, amount_dimension>
{
    using _base = details::unit_t<double, std::micro, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micromole"};
    static constexpr std::string_view symbol{"umol"};
    static constexpr std::wstring_view w_symbol{L"µmol"};
    static constexpr std::u8string_view u8_symbol{u8"µmol"};
};

struct nanomole_t final : public details::unit_t<double, std::nano, amount_dimension>
{
    using _base = details::unit_t<double, std::nano, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanomole"};
    static constexpr std::string_view symbol{"nmol"};
    static constexpr std::wstring_view w_symbol{L"nmol"};
    static constexpr std::u8string_view u8_symbol{u8"nmol"};
};

struct kilomole_t final : public details::unit_t<double, std::kilo, amount_dimension>
{
    using _base = details::unit_t<double, std::kilo, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilomole"};
    static constexpr std::string_view symbol{"kmol"};
    static constexpr std::wstring_view w_symbol{L"kmol"};
    static constexpr std::u8string_view u8_symbol{u8"kmol"};
};

}  // namespace PKR_UNITS_NAMESPACE