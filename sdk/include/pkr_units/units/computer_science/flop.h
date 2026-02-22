#pragma once

#include <string_view>
#include <ratio>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

// Tags used to distinguish flop-related units
struct flop_amount_tag
{
};

struct flop_rate_tag
{
};

namespace PKR_UNITS_NAMESPACE
{
// ----------------------------- FLOPs (floating-point operations) -----------
template <is_unit_value_type_c T>
struct flop_t final : public unit_t<T, std::ratio<1, 1>, amount_dimension, flop_amount_tag>
{
    using _base = unit_t<T, std::ratio<1, 1>, amount_dimension, flop_amount_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"floating-point operation"};
    [[maybe_unused]] static constexpr std::string_view symbol{"FLOP"};
};

template <is_unit_value_type_c T>
flop_t(T) -> flop_t<T>;

template <is_unit_value_type_c T>
struct megaflop_t final : public unit_t<T, std::mega, amount_dimension, flop_amount_tag>
{
    using _base = unit_t<T, std::mega, amount_dimension, flop_amount_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megaflop"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MFLOP"};
};

template <is_unit_value_type_c T>
megaflop_t(T) -> megaflop_t<T>;

// performance rates (flops per second)

template <is_unit_value_type_c T>
struct flop_per_second_t final : public unit_t<T, std::ratio<1, 1>, amount_rate_dimension, flop_rate_tag>
{
    using _base = unit_t<T, std::ratio<1, 1>, amount_rate_dimension, flop_rate_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"flop per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"flop/s"};
};

template <is_unit_value_type_c T>
flop_per_second_t(T) -> flop_per_second_t<T>;

template <is_unit_value_type_c T>
struct megaflop_per_second_t final : public unit_t<T, std::mega, amount_rate_dimension, flop_rate_tag>
{
    using _base = unit_t<T, std::mega, amount_rate_dimension, flop_rate_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megaflop per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MFLOP/s"};
};

template <is_unit_value_type_c T>
megaflop_per_second_t(T) -> megaflop_per_second_t<T>;

// Derived mapping for FLOP family
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, amount_dimension, flop_amount_tag>
{
    using type = flop_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::mega, amount_dimension, flop_amount_tag>
{
    using type = megaflop_t<T>;
};

// rate specializations
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, amount_rate_dimension, flop_rate_tag>
{
    using type = flop_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::mega, amount_rate_dimension, flop_rate_tag>
{
    using type = megaflop_per_second_t<T>;
};

} // namespace PKR_UNITS_NAMESPACE
