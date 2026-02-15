#pragma once

// This header contains formatting specializations and helpers
// for electrical / complex-valued unit types.
// It was renamed from complex_unit_formatting.h to better
// reflect its focus on electrical engineering notation (use of 'j', etc.).

#include <algorithm>
#include <format>
#include <string_view>
#include <type_traits>
#include <cmath>
#include <complex>
#include <cctype>
#include <array>

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/formatting/unit_formatting_traits.h>

namespace std
{

// Stack-based output iterator for formatting into a fixed array (no allocation)
template <typename CharT>
class stack_array_iterator
{
    std::array<CharT, 128>* m_buffer;
    std::size_t* m_pos;

public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = std::ptrdiff_t;
    using pointer = void;
    using reference = void;

    constexpr stack_array_iterator(std::array<CharT, 128>& buf, std::size_t& pos)
        : m_buffer(&buf)
        , m_pos(&pos)
    {
    }

    // Pointers are trivially copyable and assignable - automatic support for output_iterator
    stack_array_iterator(const stack_array_iterator&) = default;
    stack_array_iterator& operator=(const stack_array_iterator&) = default;

    stack_array_iterator& operator*()
    {
        return *this;
    }

    stack_array_iterator& operator++()
    {
        return *this;
    }

    stack_array_iterator& operator++(int)
    {
        return *this;
    }

    stack_array_iterator& operator=(CharT c)
    {
        if (*m_pos < m_buffer->size())
        {
            (*m_buffer)[*m_pos] = c;
        }
        ++*m_pos;
        return *this;
    }
};

// Helper: format a value into a stack buffer and copy to format_buffer
template <typename Real, typename CharT>
inline void format_to_stack_buffer(PKR_UNITS_NAMESPACE::impl::format_buffer<CharT>& buf, const Real& value)
{
    std::array<CharT, 128> temp_buf;
    std::size_t pos = 0;
    auto it = stack_array_iterator<CharT>(temp_buf, pos);
    std::format_to(it, "{}", value);
    for (std::size_t i = 0; i < pos; ++i)
    {
        buf.push_back(temp_buf[i]);
    }
}

// Specialization for complex-valued base unit_t types
template <typename Real, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::details::unit_t<std::complex<Real>, ratio_t, dim_v>, CharT>
{
    std::formatter<Real, CharT> value_formatter;
    mutable std::basic_string_view<CharT> saved_format_spec;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        auto ret = value_formatter.parse(ctx);
        saved_format_spec = std::basic_string_view<CharT>(it, ret);
        return ret;
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::details::unit_t<std::complex<Real>, ratio_t, dim_v>& unit, FormatContext& ctx) const
    {
        auto out = ctx.out();
        const auto v = unit.value();
        const Real real = std::real(v);
        const Real imag = std::imag(v);

        // If requested scientific-style formatting and both parts share exponent, factor it
        bool has_e = false;
        for (CharT c : saved_format_spec)
        {
            if (c == static_cast<CharT>('e') || c == static_cast<CharT>('E'))
            {
                has_e = true;
                break;
            }
        }
        if (has_e && real != static_cast<Real>(0) && imag != static_cast<Real>(0))
        {
            auto compute_exp = [](Real x) -> int { return static_cast<int>(std::floor(std::log10(std::abs(static_cast<double>(x))))); };
            int exp_r = compute_exp(real);
            int exp_i = compute_exp(imag);
            if (exp_r == exp_i)
            {
                int exp = exp_r;
                Real mant_r = real / std::pow(10.0, exp);
                Real mant_i = imag / std::pow(10.0, exp);

                PKR_UNITS_NAMESPACE::impl::format_buffer<CharT> buf;
                buf.push_back(static_cast<CharT>('('));

                // Format real mantissa into temp buffer, then copy to main
                format_to_stack_buffer<Real, CharT>(buf, mant_r);
                if (mant_i >= static_cast<Real>(0))
                {
                    buf.push_back(static_cast<CharT>(' '));
                    buf.push_back(static_cast<CharT>('+'));
                    buf.push_back(static_cast<CharT>(' '));
                    buf.push_back(static_cast<CharT>('j'));
                }
                else
                {
                    buf.push_back(static_cast<CharT>(' '));
                    buf.push_back(static_cast<CharT>('-'));
                    buf.push_back(static_cast<CharT>(' '));
                    buf.push_back(static_cast<CharT>('j'));
                }
                format_to_stack_buffer<Real, CharT>(buf, std::abs(mant_i));
                buf.push_back(static_cast<CharT>(')'));
                buf.push_back(static_cast<CharT>(' '));

                // Use trait dispatch for multiplication sign
                buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::multiply_sign());
                buf.push_back(static_cast<CharT>('1'));
                buf.push_back(static_cast<CharT>('0'));

                // Build exponent as superscript
                int e = exp;
                if (e < 0)
                {
                    buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::superscript_minus());
                    e = -e;
                }
                if (e == 0)
                {
                    buf.append(PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(0));
                }
                else
                {
                    std::array<int, 10> digits{};
                    std::size_t digit_count = 0;
                    while (e > 0 && digit_count < 10)
                    {
                        digits[digit_count++] = e % 10;
                        e /= 10;
                    }
                    // digits are collected least-significant-first; iterate backwards
                    for (std::size_t i = digit_count; i > 0; --i)
                    {
                        buf.append(PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(digits[i - 1]));
                    }
                }

                buf.push_back(static_cast<CharT>(' '));

                // Build dimension symbol inline (avoid re-entrancy of global buffer)
                const int dims[] = {
                    dim_v.mass, dim_v.length, dim_v.time, dim_v.current, dim_v.temperature, dim_v.amount, dim_v.intensity, dim_v.angle, dim_v.star_angle};
                const auto& symbols = PKR_UNITS_NAMESPACE::impl::base_unit_symbols<CharT>;
                bool first_dim = true;
                for (std::size_t i = 0; i < 9; ++i)
                {
                    if (dims[i] != 0)
                    {
                        if (!first_dim)
                        {
                            buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::separator());
                        }
                        first_dim = false;

                        buf.append(symbols[i]);
                        if (dims[i] != 1)
                        {
                            bool negative_exp = dims[i] < 0;
                            int abs_exp = negative_exp ? -dims[i] : dims[i];

                            buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::superscript_caret());
                            if (negative_exp)
                            {
                                buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::superscript_minus());
                            }

                            // Extract digits without heap allocation
                            std::array<int, 10> temp_digits{};
                            std::size_t temp_count = 0;
                            int temp_val = abs_exp;
                            while (temp_val > 0 && temp_count < 10)
                            {
                                temp_digits[temp_count++] = temp_val % 10;
                                temp_val /= 10;
                            }
                            if (temp_count == 0)
                            {
                                temp_digits[temp_count++] = 0;
                            }
                            // Output digits in correct order (reverse of collected)
                            for (std::size_t idx = temp_count; idx > 0; --idx)
                            {
                                buf.append(PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(temp_digits[idx - 1]));
                            }
                        }
                    }
                }

                return std::copy(buf.begin(), buf.end(), out);
            }
        }

        // Fallback: default formatting (no factoring)
        // Use a buffer for the composed string
        PKR_UNITS_NAMESPACE::impl::format_buffer<CharT> buf;

        // (real [+-] jimag)
        buf.push_back(static_cast<CharT>('('));

        // Format real part into temp buffer, then copy to main
        format_to_stack_buffer<Real, CharT>(buf, real);

        if (imag >= static_cast<Real>(0))
        {
            buf.push_back(static_cast<CharT>(' '));
            buf.push_back(static_cast<CharT>('+'));
            buf.push_back(static_cast<CharT>(' '));
            buf.push_back(static_cast<CharT>('j'));
        }
        else
        {
            buf.push_back(static_cast<CharT>(' '));
            buf.push_back(static_cast<CharT>('-'));
            buf.push_back(static_cast<CharT>(' '));
            buf.push_back(static_cast<CharT>('j'));
        }

        // Format imaginary part into temp buffer, then copy to main
        format_to_stack_buffer<Real, CharT>(buf, std::abs(imag));

        buf.push_back(static_cast<CharT>(')'));

        // Build dimension symbol inline (avoid re-entrancy of global buffer)
        buf.push_back(static_cast<CharT>(' '));
        const int dims[] = {
            dim_v.mass, dim_v.length, dim_v.time, dim_v.current, dim_v.temperature, dim_v.amount, dim_v.intensity, dim_v.angle, dim_v.star_angle};
        const auto& symbols = PKR_UNITS_NAMESPACE::impl::base_unit_symbols<CharT>;
        bool first_dim = true;
        for (std::size_t i = 0; i < 9; ++i)
        {
            if (dims[i] != 0)
            {
                if (!first_dim)
                {
                    buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::separator());
                }
                first_dim = false;

                buf.append(symbols[i]);
                if (dims[i] != 1)
                {
                    bool negative_exp = dims[i] < 0;
                    int abs_exp = negative_exp ? -dims[i] : dims[i];

                    buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::superscript_caret());
                    if (negative_exp)
                    {
                        buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::superscript_minus());
                    }

                    // Extract digits without heap allocation
                    std::array<int, 10> temp_digits{};
                    std::size_t temp_count = 0;
                    int temp_val = abs_exp;
                    while (temp_val > 0 && temp_count < 10)
                    {
                        temp_digits[temp_count++] = temp_val % 10;
                        temp_val /= 10;
                    }
                    if (temp_count == 0)
                    {
                        temp_digits[temp_count++] = 0;
                    }
                    // Output digits in correct order (reverse of collected)
                    for (std::size_t idx = temp_count; idx > 0; --idx)
                    {
                        buf.append(PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(temp_digits[idx - 1]));
                    }
                }
            }
        }

        return std::copy(buf.begin(), buf.end(), out);
    }
};

// Specialization for derived unit types with complex value_type
template <typename T, typename CharT>
    requires(
        PKR_UNITS_NAMESPACE::is_derived_pkr_unit_c<T> &&
        PKR_UNITS_NAMESPACE::is_std_complex_c<typename PKR_UNITS_NAMESPACE::details::is_pkr_unit<T>::value_type>)
struct formatter<T, CharT>
{
    using complex_t = typename PKR_UNITS_NAMESPACE::details::is_pkr_unit<T>::value_type;
    using real_t = typename complex_t::value_type;

    std::formatter<real_t, CharT> value_formatter;
    mutable std::basic_string_view<CharT> saved_format_spec;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        auto ret = value_formatter.parse(ctx);
        saved_format_spec = std::basic_string_view<CharT>(it, ret);
        return ret;
    }

    template <typename FormatContext>
    auto format(const T& unit, FormatContext& ctx) const
    {
        auto out = ctx.out();
        const complex_t v = unit.value();
        const real_t real = std::real(v);
        const real_t imag = std::imag(v);

        // Helper to select appropriate symbol based on character type
        auto get_symbol = []() -> std::basic_string_view<CharT>
        {
            if constexpr (std::is_same_v<CharT, char>)
            {
                return T::symbol;
            }
            else if constexpr (std::is_same_v<CharT, char8_t>)
            {
                return T::u8_symbol;
            }
            else if constexpr (std::is_same_v<CharT, wchar_t>)
            {
                return T::w_symbol;
            }
            else
            {
                return T::symbol;
            }
        };

        // If requested scientific-style formatting and both parts share exponent, factor it
        bool has_e = false;
        for (CharT c : saved_format_spec)
        {
            if (c == static_cast<CharT>('e') || c == static_cast<CharT>('E'))
            {
                has_e = true;
                break;
            }
        }
        if (has_e && (real != static_cast<real_t>(0) && imag != static_cast<real_t>(0)))
        {
            auto compute_exp = [](real_t x) -> int { return static_cast<int>(std::floor(std::log10(std::abs(static_cast<double>(x))))); };
            int exp_r = compute_exp(real);
            int exp_i = compute_exp(imag);
            if (exp_r == exp_i)
            {
                int exp = exp_r;
                real_t mant_r = real / std::pow(10.0, exp);
                real_t mant_i = imag / std::pow(10.0, exp);

                // Format mantissas into buffers (no dynamic allocation)
                // Using format_to_stack_buffer for the actual formatting
                PKR_UNITS_NAMESPACE::impl::format_buffer<CharT> buf;

                buf.push_back(static_cast<CharT>('('));
                format_to_stack_buffer<real_t, CharT>(buf, mant_r);
                if (mant_i >= static_cast<real_t>(0))
                {
                    buf.push_back(static_cast<CharT>(' '));
                    buf.push_back(static_cast<CharT>('+'));
                    buf.push_back(static_cast<CharT>(' '));
                    buf.push_back(static_cast<CharT>('j'));
                }
                else
                {
                    buf.push_back(static_cast<CharT>(' '));
                    buf.push_back(static_cast<CharT>('-'));
                    buf.push_back(static_cast<CharT>(' '));
                    buf.push_back(static_cast<CharT>('j'));
                }
                format_to_stack_buffer<real_t, CharT>(buf, std::abs(mant_i));
                buf.push_back(static_cast<CharT>(')'));
                buf.push_back(static_cast<CharT>(' '));

                // Use trait dispatch for multiplication sign
                buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::multiply_sign());
                buf.push_back(static_cast<CharT>('1'));
                buf.push_back(static_cast<CharT>('0'));
                buf.push_back(static_cast<CharT>('^')); // Caret before exponent digits

                // Build exponent as superscript
                int e = exp;
                if (e < 0)
                {
                    buf.append(PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::superscript_minus());
                    e = -e;
                }
                if (e == 0)
                {
                    buf.append(PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(0));
                }
                else
                {
                    std::array<int, 10> digits{};
                    std::size_t digit_count = 0;
                    while (e > 0 && digit_count < 10)
                    {
                        digits[digit_count++] = e % 10;
                        e /= 10;
                    }
                    // digits are collected least-significant-first; iterate backwards
                    for (std::size_t i = digit_count; i > 0; --i)
                    {
                        buf.append(PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(digits[i - 1]));
                    }
                }

                buf.push_back(static_cast<CharT>(' '));
                buf.append(get_symbol());

                return std::copy(buf.begin(), buf.end(), out);
            }
        }

        // Fallback: default formatting (no factoring)
        // Use a buffer for the composed string
        PKR_UNITS_NAMESPACE::impl::format_buffer<CharT> buf;

        // (real [+-] jimag)
        buf.push_back(static_cast<CharT>('('));

        // Format real part into temp buffer, then copy to main
        format_to_stack_buffer<real_t, CharT>(buf, real);

        if (imag >= static_cast<real_t>(0))
        {
            buf.push_back(static_cast<CharT>(' '));
            buf.push_back(static_cast<CharT>('+'));
            buf.push_back(static_cast<CharT>(' '));
            buf.push_back(static_cast<CharT>('j'));
        }
        else
        {
            buf.push_back(static_cast<CharT>(' '));
            buf.push_back(static_cast<CharT>('-'));
            buf.push_back(static_cast<CharT>(' '));
            buf.push_back(static_cast<CharT>('j'));
        }

        // Format imaginary part into temp buffer, then copy to main
        format_to_stack_buffer<real_t, CharT>(buf, std::abs(imag));

        buf.push_back(static_cast<CharT>(')'));

        // Space before symbol
        buf.push_back(static_cast<CharT>(' '));
        buf.append(get_symbol());

        return std::copy(buf.begin(), buf.end(), out);
    }
};

} // namespace std
