#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/decls/josephson_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Josephson constant unit
// Base unit: Hz/V (Josephson constant)
template <is_unit_value_type_c T>
struct josephson_t final : public details::unit_t<T, std::ratio<1, 1>, josephson_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, josephson_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"josephson"};
    [[maybe_unused]] static constexpr std::string_view symbol{"K_J"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"K_J"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"K_J"};
};

template <is_unit_value_type_c T>
josephson_t(T) -> josephson_t<T>;
} // namespace PKR_UNITS_NAMESPACE
