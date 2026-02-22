#pragma once

#include <string_view>
#include <ratio>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

// Tag used to distinguish byte-based amount units
struct byte_tag
{
}; // simple declaration, no guards

namespace PKR_UNITS_NAMESPACE
{
// ----------------------------- Bytes (binary-prefixed by default) ----------
// NOTE: per project convention requested: `byte` SI-like prefixes use
// binary multiples (powers of two). `kilobyte_t` therefore equals 1024 bytes.

template <is_unit_value_type_c T>
struct byte_t final : public unit_t<T, std::ratio<1, 1>, amount_dimension, byte_tag>
{
    using _base = unit_t<T, std::ratio<1, 1>, amount_dimension, byte_tag>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"byte"};
    [[maybe_unused]] static constexpr std::string_view symbol{"B"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"B"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"B"};
};

template <is_unit_value_type_c T>
byte_t(T) -> byte_t<T>;

// kilobyte: 1024 bytes (binary)
template <is_unit_value_type_c T>
struct kilobyte_t final : public unit_t<T, std::ratio<1024, 1>, amount_dimension, byte_tag>
{
    using _base = unit_t<T, std::ratio<1024, 1>, amount_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilobyte"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kB"};
};

template <is_unit_value_type_c T>
kilobyte_t(T) -> kilobyte_t<T>;

// metric (decimal) prefixes for bytes – less common but occasionally used
template <is_unit_value_type_c T>
struct megabyte_t final : public unit_t<T, std::mega, amount_dimension, byte_tag>
{
    using _base = unit_t<T, std::mega, amount_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megabyte"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MB"};
};

template <is_unit_value_type_c T>
megabyte_t(T) -> megabyte_t<T>;

template <is_unit_value_type_c T>
struct gigabyte_t final : public unit_t<T, std::ratio<1000000000, 1>, amount_dimension, byte_tag>
{
    using _base = unit_t<T, std::ratio<1000000000, 1>, amount_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigabyte"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GB"};
};

template <is_unit_value_type_c T>
gigabyte_t(T) -> gigabyte_t<T>;

// bandwidth with bytes per second (reuses byte_tag)
template <is_unit_value_type_c T>
struct byte_per_second_t final : public unit_t<T, std::ratio<1, 1>, amount_rate_dimension, byte_tag>
{
    using _base = unit_t<T, std::ratio<1, 1>, amount_rate_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"byte per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"B/s"};
};

template <is_unit_value_type_c T>
byte_per_second_t(T) -> byte_per_second_t<T>;

template <is_unit_value_type_c T>
struct kilobyte_per_second_t final : public unit_t<T, std::ratio<1024, 1>, amount_rate_dimension, byte_tag>
{
    using _base = unit_t<T, std::ratio<1024, 1>, amount_rate_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilobyte per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kB/s"};
};

template <is_unit_value_type_c T>
kilobyte_per_second_t(T) -> kilobyte_per_second_t<T>;

// metric prefixes
template <is_unit_value_type_c T>
struct megabyte_per_second_t final : public unit_t<T, std::mega, amount_rate_dimension, byte_tag>
{
    using _base = unit_t<T, std::mega, amount_rate_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megabyte per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MB/s"};
};

template <is_unit_value_type_c T>
megabyte_per_second_t(T) -> megabyte_per_second_t<T>;

template <is_unit_value_type_c T>
struct gigabyte_per_second_t final : public unit_t<T, std::ratio<1000000000, 1>, amount_rate_dimension, byte_tag>
{
    using _base = unit_t<T, std::ratio<1000000000, 1>, amount_rate_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigabyte per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GB/s"};
};

template <is_unit_value_type_c T>
gigabyte_per_second_t(T) -> gigabyte_per_second_t<T>;

// Keep explicit IEC names as well (aliases with same ratio for binary prefixes)
template <is_unit_value_type_c T>
struct kibibyte_t final : public unit_t<T, std::ratio<1024, 1>, amount_dimension, byte_tag>
{
    using _base = unit_t<T, std::ratio<1024, 1>, amount_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kibibyte"};
    [[maybe_unused]] static constexpr std::string_view symbol{"KiB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"KiB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"KiB"};
};

template <is_unit_value_type_c T>
kibibyte_t(T) -> kibibyte_t<T>;

template <is_unit_value_type_c T>
struct mebibyte_t final : public unit_t<T, std::ratio<1048576, 1>, amount_dimension, byte_tag>
{
    using _base = unit_t<T, std::ratio<1048576, 1>, amount_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"mebibyte"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MiB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MiB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MiB"};
};

template <is_unit_value_type_c T>
mebibyte_t(T) -> mebibyte_t<T>;

template <is_unit_value_type_c T>
struct gibibyte_t final : public unit_t<T, std::ratio<1073741824, 1>, amount_dimension, byte_tag>
{
    using _base = unit_t<T, std::ratio<1073741824, 1>, amount_dimension, byte_tag>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gibibyte"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GiB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GiB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GiB"};
};

template <is_unit_value_type_c T>
gibibyte_t(T) -> gibibyte_t<T>;

// Most-derived specializations (bytes family)
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, amount_dimension, byte_tag>
{
    using type = byte_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1024, 1>, amount_dimension, byte_tag>
{
    using type = kilobyte_t<T>;
};

// metric bytes
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::mega, amount_dimension, byte_tag>
{
    using type = megabyte_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1000000000, 1>, amount_dimension, byte_tag>
{
    using type = gigabyte_t<T>;
};

// binary prefixes
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1048576, 1>, amount_dimension, byte_tag>
{
    using type = mebibyte_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1073741824, 1>, amount_dimension, byte_tag>
{
    using type = gibibyte_t<T>;
};

// per-second specializations
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, amount_rate_dimension, byte_tag>
{
    using type = byte_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1024, 1>, amount_rate_dimension, byte_tag>
{
    using type = kilobyte_per_second_t<T>;
};

// metric
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::mega, amount_rate_dimension, byte_tag>
{
    using type = megabyte_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1000000000, 1>, amount_rate_dimension, byte_tag>
{
    using type = gigabyte_per_second_t<T>;
};

} // namespace PKR_UNITS_NAMESPACE
