#pragma once

#include <string_view>
#include <ratio>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

#ifndef PKR_UNITS_COMPUTER_SCIENCE_BIT_TAG
#define PKR_UNITS_COMPUTER_SCIENCE_BIT_TAG

struct bit_tag
{
};
#endif

namespace PKR_UNITS_NAMESPACE
{
// ----------------------------- Bits (decimal scaling for network speeds) --
// Bits are represented as a fraction of a byte (1 bit = 1/8 byte). Network
// conventions typically use decimal (1000) prefixes for bits.

template <is_unit_value_type_c T>
struct bit_t final : public unit_t<T, std::ratio<1, 8>, amount_dimension, bit_tag>
{
    using _base = unit_t<T, std::ratio<1, 8>, amount_dimension, bit_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"bit"};
    [[maybe_unused]] static constexpr std::string_view symbol{"b"};
};

template <is_unit_value_type_c T>
bit_t(T) -> bit_t<T>;

// kilobit/megabit/gigabit use decimal multiples of `bit` (1000^n × bit)
template <is_unit_value_type_c T>
struct kilobit_t final : public unit_t<T, std::ratio<1000, 8>, amount_dimension, bit_tag>
{
    using _base = unit_t<T, std::ratio<1000, 8>, amount_dimension, bit_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilobit"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kb"};
};

template <is_unit_value_type_c T>
kilobit_t(T) -> kilobit_t<T>;

template <is_unit_value_type_c T>
struct megabit_t final : public unit_t<T, std::ratio<1000000, 8>, amount_dimension, bit_tag>
{
    using _base = unit_t<T, std::ratio<1000000, 8>, amount_dimension, bit_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megabit"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Mb"};
};

template <is_unit_value_type_c T>
megabit_t(T) -> megabit_t<T>;

template <is_unit_value_type_c T>
struct gigabit_t final : public unit_t<T, std::ratio<1000000000, 8>, amount_dimension, bit_tag>
{
    using _base = unit_t<T, std::ratio<1000000000, 8>, amount_dimension, bit_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigabit"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gb"};
};

// bandwidth units (bits per second) reuse the same tag but different dimension
// (amount per time).  prefixes mirror the bit family.

template <is_unit_value_type_c T>
struct bit_per_second_t final : public unit_t<T, std::ratio<1, 8>, amount_rate_dimension, bit_tag>
{
    using _base = unit_t<T, std::ratio<1, 8>, amount_rate_dimension, bit_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"bit per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"b/s"};
};

template <is_unit_value_type_c T>
bit_per_second_t(T) -> bit_per_second_t<T>;

template <is_unit_value_type_c T>
struct kilobit_per_second_t final : public unit_t<T, std::ratio<1000, 8>, amount_rate_dimension, bit_tag>
{
    using _base = unit_t<T, std::ratio<1000, 8>, amount_rate_dimension, bit_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilobit per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kb/s"};
};

template <is_unit_value_type_c T>
kilobit_per_second_t(T) -> kilobit_per_second_t<T>;

template <is_unit_value_type_c T>
struct megabit_per_second_t final : public unit_t<T, std::ratio<1000000, 8>, amount_rate_dimension, bit_tag>
{
    using _base = unit_t<T, std::ratio<1000000, 8>, amount_rate_dimension, bit_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megabit per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Mb/s"};
};

template <is_unit_value_type_c T>
megabit_per_second_t(T) -> megabit_per_second_t<T>;

template <is_unit_value_type_c T>
struct gigabit_per_second_t final : public unit_t<T, std::ratio<1000000000, 8>, amount_rate_dimension, bit_tag>
{
    using _base = unit_t<T, std::ratio<1000000000, 8>, amount_rate_dimension, bit_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigabit per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gb/s"};
};

template <is_unit_value_type_c T>
gigabit_per_second_t(T) -> gigabit_per_second_t<T>;

template <is_unit_value_type_c T>
gigabit_t(T) -> gigabit_t<T>;

// Most-derived specializations (bit family)
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 8>, amount_dimension, bit_tag>
{
    using type = bit_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1000, 8>, amount_dimension, bit_tag>
{
    using type = kilobit_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1000000, 8>, amount_dimension, bit_tag>
{
    using type = megabit_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1000000000, 8>, amount_dimension, bit_tag>
{
    using type = gigabit_t<T>;
};

// per-second specializations
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 8>, amount_rate_dimension, bit_tag>
{
    using type = bit_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1000, 8>, amount_rate_dimension, bit_tag>
{
    using type = kilobit_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1000000, 8>, amount_rate_dimension, bit_tag>
{
    using type = megabit_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1000000000, 8>, amount_rate_dimension, bit_tag>
{
    using type = gigabit_per_second_t<T>;
};

} // namespace PKR_UNITS_NAMESPACE
