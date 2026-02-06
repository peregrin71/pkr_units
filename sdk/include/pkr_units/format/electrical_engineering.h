#pragma once

// This header contains formatting specializations and helpers
// for electrical / complex-valued unit types.
// It was renamed from complex_unit_formatting.h to better
// reflect its focus on electrical engineering notation (use of 'j', etc.).

#include <algorithm>
#include <format>
#include <string>
#include <string_view>
#include <type_traits>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <complex>
#include <vector>
#include <cctype>

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/formatting/unit_formatting_traits.h>

namespace std
{

// Specialization for complex-valued base unit_t types
template <typename Real, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::details::unit_t<std::complex<Real>, ratio_t, dim_v>, CharT>
{
    std::formatter<Real, CharT> value_formatter;
    mutable std::basic_string<CharT> saved_format_spec;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        auto ret = value_formatter.parse(ctx);
        saved_format_spec = std::basic_string<CharT>(it, ret);
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

                // Build mantissa format spec (drop the 'e' if present)
                std::basic_string<CharT> mantissa_spec = saved_format_spec;
                auto pos = mantissa_spec.find(static_cast<CharT>('e'));
                if (pos == std::basic_string<CharT>::npos)
                    pos = mantissa_spec.find(static_cast<CharT>('E'));
                if (pos != std::basic_string<CharT>::npos)
                    mantissa_spec.erase(pos);

                // Derive precision from mantissa_spec if present (e.g. ".1e" -> precision 1)
                int precision = 6;
                auto dotpos = mantissa_spec.find(static_cast<CharT>('.'));
                if (dotpos != std::basic_string<CharT>::npos)
                {
                    size_t p = dotpos + 1;
                    int val = 0;
                    while (p < mantissa_spec.size() && std::isdigit(static_cast<unsigned char>(mantissa_spec[p])))
                    {
                        val = val * 10 + (mantissa_spec[p] - '0');
                        ++p;
                    }
                    if (val > 0)
                        precision = val;
                }

                std::ostringstream oss_r;
                oss_r.setf(std::ios::fixed);
                oss_r << std::setprecision(precision) << mant_r;
                std::string fmt_r = oss_r.str();

                std::ostringstream oss_i;
                oss_i.setf(std::ios::fixed);
                oss_i << std::setprecision(precision) << std::abs(mant_i);
                std::string fmt_i = oss_i.str();

                // Build exponent as superscript using traits
                std::basic_string<CharT> exp_sup;
                int e = exp;
                if (e < 0)
                {
                    exp_sup += PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::superscript_minus();
                    e = -e;
                }
                if (e == 0)
                    exp_sup += PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(0);
                else
                {
                    std::vector<std::basic_string_view<CharT>> digits;
                    while (e > 0)
                    {
                        int d = e % 10;
                        digits.emplace_back(PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(d));
                        e /= 10;
                    }
                    // digits are collected least-significant-first; append in reverse
                    for (auto it = digits.rbegin(); it != digits.rend(); ++it)
                        exp_sup += *it;
                }

                // Compose final string: (mant_r [+-] jmant_i) multiply_sign 10 exp_sup sym
                std::basic_string<CharT> composed;
                for (char c : fmt_r)
                    composed += static_cast<CharT>(c);
                if (mant_i >= static_cast<Real>(0))
                {
                    composed += static_cast<CharT>(' ');
                    composed += static_cast<CharT>('+');
                    composed += static_cast<CharT>(' ');
                    composed += static_cast<CharT>('j');
                }
                else
                {
                    composed += static_cast<CharT>(' ');
                    composed += static_cast<CharT>('-');
                    composed += static_cast<CharT>(' ');
                    composed += static_cast<CharT>('j');
                }
                for (char c : fmt_i)
                    composed += static_cast<CharT>(c);
                composed += static_cast<CharT>(')');
                composed += static_cast<CharT>(' ');

                // Use trait dispatch for multiplication sign
                composed += PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::multiply_sign();
                composed += static_cast<CharT>('1');
                composed += static_cast<CharT>('0');
                composed += exp_sup;
                composed += static_cast<CharT>(' ');

                auto dim_sym = PKR_UNITS_NAMESPACE::impl::build_dimension_symbol<CharT>(dim_v);
                if (!dim_sym.empty())
                {
                    composed += dim_sym;
                }

                return std::copy(composed.begin(), composed.end(), out);
            }
        }

        // Fallback: default formatting (no factoring)
        // (real [+-] jimag)
        *out++ = static_cast<CharT>('(');
        out = value_formatter.format(real, ctx);

        if (imag >= static_cast<Real>(0))
        {
            *out++ = static_cast<CharT>(' ');
            *out++ = static_cast<CharT>('+');
            *out++ = static_cast<CharT>(' ');
            *out++ = static_cast<CharT>('j');
            out = value_formatter.format(imag, ctx);
        }
        else
        {
            *out++ = static_cast<CharT>(' ');
            *out++ = static_cast<CharT>('-');
            *out++ = static_cast<CharT>(' ');
            *out++ = static_cast<CharT>('j');
            out = value_formatter.format(-imag, ctx);
        }

        *out++ = static_cast<CharT>(')');
        // For base unit_t, always build dimension symbol
        static const std::basic_string<CharT> built = []() { return PKR_UNITS_NAMESPACE::impl::build_dimension_symbol<CharT>(dim_v); }();
        std::basic_string_view<CharT> sym = built;

        // Space before symbol
        *out++ = static_cast<CharT>(' ');
        return std::copy(sym.begin(), sym.end(), out);
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
    mutable std::basic_string<CharT> saved_format_spec;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        auto ret = value_formatter.parse(ctx);
        saved_format_spec = std::basic_string<CharT>(it, ret);
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
                return T::symbol;
            else if constexpr (std::is_same_v<CharT, char8_t>)
                return T::u8_symbol;
            else if constexpr (std::is_same_v<CharT, wchar_t>)
                return T::w_symbol;
            else
                return T::symbol;
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

                // Build mantissa format spec (drop the 'e' if present)
                std::basic_string<CharT> mantissa_spec = saved_format_spec;
                auto pos = mantissa_spec.find(static_cast<CharT>('e'));
                if (pos == std::basic_string<CharT>::npos)
                    pos = mantissa_spec.find(static_cast<CharT>('E'));
                if (pos != std::basic_string<CharT>::npos)
                    mantissa_spec.erase(pos);

                // Derive precision from mantissa_spec if present (e.g. ".1e" -> precision 1)
                int precision = 6;
                auto dotpos = mantissa_spec.find(static_cast<CharT>('.'));
                if (dotpos != std::basic_string<CharT>::npos)
                {
                    size_t p = dotpos + 1;
                    int val = 0;
                    while (p < mantissa_spec.size() && std::isdigit(static_cast<unsigned char>(mantissa_spec[p])))
                    {
                        val = val * 10 + (mantissa_spec[p] - '0');
                        ++p;
                    }
                    if (val > 0)
                        precision = val;
                }

                std::ostringstream oss_r;
                oss_r.setf(std::ios::fixed);
                oss_r << std::setprecision(precision) << mant_r;
                std::string fmt_r = oss_r.str();

                std::ostringstream oss_i;
                oss_i.setf(std::ios::fixed);
                oss_i << std::setprecision(precision) << std::abs(mant_i);
                std::string fmt_i = oss_i.str();

                // Build exponent as superscript using traits
                std::basic_string<CharT> exp_sup;
                int e = exp;
                if (e < 0)
                {
                    exp_sup += PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::superscript_minus();
                    e = -e;
                }
                if (e == 0)
                    exp_sup += PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(0);
                else
                {
                    std::vector<std::basic_string_view<CharT>> digits;
                    while (e > 0)
                    {
                        int d = e % 10;
                        digits.emplace_back(PKR_UNITS_NAMESPACE::impl::superscript_digit_lookup<CharT>(d));
                        e /= 10;
                    }
                    // digits collected least-significant-first; append in reverse order
                    for (auto it = digits.rbegin(); it != digits.rend(); ++it)
                        exp_sup += *it;
                }

                // Compose final string: (mant_r [+-] jmant_i) multiply_sign 10 exp_sup sym
                std::basic_string<CharT> composed;
                composed += static_cast<CharT>('(');
                for (char c : fmt_r)
                    composed += static_cast<CharT>(c);
                if (mant_i >= static_cast<real_t>(0))
                {
                    composed += static_cast<CharT>(' ');
                    composed += static_cast<CharT>('+');
                    composed += static_cast<CharT>(' ');
                    composed += static_cast<CharT>('j');
                }
                else
                {
                    composed += static_cast<CharT>(' ');
                    composed += static_cast<CharT>('-');
                    composed += static_cast<CharT>(' ');
                    composed += static_cast<CharT>('j');
                }
                for (char c : fmt_i)
                    composed += static_cast<CharT>(c);
                composed += static_cast<CharT>(')');
                composed += static_cast<CharT>(' ');

                // Use trait dispatch for multiplication sign
                composed += PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::multiply_sign();
                composed += static_cast<CharT>('1');
                composed += static_cast<CharT>('0');
                composed += static_cast<CharT>('^'); // Caret before exponent digits
                composed += exp_sup;
                composed += static_cast<CharT>(' ');

                composed += get_symbol();

                return std::copy(composed.begin(), composed.end(), out);
            }
        }

        // Fallback: default formatting (no factoring)
        // (real [+-] jimag)
        *out++ = static_cast<CharT>('(');
        out = value_formatter.format(real, ctx);

        if (imag >= static_cast<real_t>(0))
        {
            *out++ = static_cast<CharT>(' ');
            *out++ = static_cast<CharT>('+');
            *out++ = static_cast<CharT>(' ');
            *out++ = static_cast<CharT>('j');
            out = value_formatter.format(imag, ctx);
        }
        else
        {
            *out++ = static_cast<CharT>(' ');
            *out++ = static_cast<CharT>('-');
            *out++ = static_cast<CharT>(' ');
            *out++ = static_cast<CharT>('j');
            out = value_formatter.format(-imag, ctx);
        }

        *out++ = static_cast<CharT>(')');

        // Space before symbol
        *out++ = static_cast<CharT>(' ');
        return std::copy(get_symbol().begin(), get_symbol().end(), out);
    }
};

} // namespace std
