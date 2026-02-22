#pragma once

#include <string_view>
#include <ratio>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

// Tags used to distinguish neural-operation units
struct neural_amount_tag
{
};

struct neural_rate_tag
{
};

namespace PKR_UNITS_NAMESPACE
{
// ----------------------------- Neural operations ---------------------------
// Separate tagged family for neural-specific ops (keeps them distinct from
// FLOPs and bytes).

template <is_unit_value_type_c T>
struct neural_op_t final : public unit_t<T, std::ratio<1, 1>, amount_dimension, neural_amount_tag>
{
    using _base = unit_t<T, std::ratio<1, 1>, amount_dimension, neural_amount_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"neural operation"};
    [[maybe_unused]] static constexpr std::string_view symbol{"NOP"};
};

template <is_unit_value_type_c T>
neural_op_t(T) -> neural_op_t<T>;

template <is_unit_value_type_c T>
struct meganeural_op_t final : public unit_t<T, std::mega, amount_dimension, neural_amount_tag>
{
    using _base = unit_t<T, std::mega, amount_dimension, neural_amount_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"meganeural operation"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MNOP"};
};

// neural ops per second

template <is_unit_value_type_c T>
struct neural_op_per_second_t final : public unit_t<T, std::ratio<1, 1>, amount_rate_dimension, neural_rate_tag>
{
    using _base = unit_t<T, std::ratio<1, 1>, amount_rate_dimension, neural_rate_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"neural ops per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"NOP/s"};
};

template <is_unit_value_type_c T>
neural_op_per_second_t(T) -> neural_op_per_second_t<T>;

template <is_unit_value_type_c T>
struct meganeural_op_per_second_t final : public unit_t<T, std::mega, amount_rate_dimension, neural_rate_tag>
{
    using _base = unit_t<T, std::mega, amount_rate_dimension, neural_rate_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"meganeural ops per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MNOP/s"};
};

template <is_unit_value_type_c T>
meganeural_op_per_second_t(T) -> meganeural_op_per_second_t<T>;

template <is_unit_value_type_c T>
meganeural_op_t(T) -> meganeural_op_t<T>;

// Derived mapping for neural-op family
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, amount_dimension, neural_amount_tag>
{
    using type = neural_op_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::mega, amount_dimension, neural_amount_tag>
{
    using type = meganeural_op_t<T>;
};

// per-second specializations
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, amount_rate_dimension, neural_rate_tag>
{
    using type = neural_op_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::mega, amount_rate_dimension, neural_rate_tag>
{
    using type = meganeural_op_per_second_t<T>;
};

} // namespace PKR_UNITS_NAMESPACE
