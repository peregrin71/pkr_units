#pragma once

#include <variant>
#include <stdexcept>
#include <utility>

namespace pkr::units
{

// C++20-compatible expected type for monadic error handling
// API-compatible with C++23's std::expected for seamless future migration
template <typename T, typename E>
class expected_t
{
    std::variant<T, E> m_data;

public:
    // Construction from value
    expected_t(const T& value)
        : m_data(value)
    {
    }

    expected_t(T&& value) noexcept(std::is_nothrow_move_constructible_v<T>)
        : m_data(std::move(value))
    {
    }

    // Construction from error
    explicit expected_t(const E& error)
        : m_data(error)
    {
    }

    explicit expected_t(E&& error) noexcept(std::is_nothrow_move_constructible_v<E>)
        : m_data(std::move(error))
    {
    }

    // In-place construction for value (index 0)
    template <typename... Args>
    expected_t(std::in_place_index_t<0>, Args&&... args)
        : m_data(std::in_place_index<0>, std::forward<Args>(args)...)
    {
    }

    // In-place construction for error (index 1)
    template <typename... Args>
    expected_t(std::in_place_index_t<1>, Args&&... args)
        : m_data(std::in_place_index<1>, std::forward<Args>(args)...)
    {
    }

    // Default move/copy semantics
    expected_t(const expected_t&) = default;
    expected_t(expected_t&&) noexcept(std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_constructible_v<E>) = default;
    expected_t& operator=(const expected_t&) = default;
    expected_t& operator=(expected_t&&) noexcept = default;

    ~expected_t() = default;

    // Status checks (C++23 compatible)
    [[nodiscard]] bool has_value() const noexcept
    {
        return std::holds_alternative<T>(m_data);
    }

    [[nodiscard]] explicit operator bool() const noexcept
    {
        return has_value();
    }

    // Value access (C++23 compatible)
    T& operator*()
    {
        return std::get<T>(m_data);
    }

    const T& operator*() const
    {
        return std::get<T>(m_data);
    }

    T* operator->()
    {
        return &std::get<T>(m_data);
    }

    const T* operator->() const
    {
        return &std::get<T>(m_data);
    }

    // Throws std::bad_variant_access if error is held (C++23 compatible)
    T& value()
    {
        return std::get<T>(m_data);
    }

    const T& value() const
    {
        return std::get<T>(m_data);
    }

    // Error access (C++23 compatible)
    E& error() &
    {
        return std::get<E>(m_data);
    }

    const E& error() const&
    {
        return std::get<E>(m_data);
    }

    E error() &&
    {
        return std::get<E>(std::move(m_data));
    }

    E error() const&&
    {
        return std::get<E>(std::move(m_data));
    }

    // Monadic operations (C++23 compatible)

    // map: Transform success value to a new type
    template <typename F>
    auto map(F&& f) const
    {
        using new_value_type = std::invoke_result_t<F, const T&>;
        if (has_value())
        {
            return expected_t<new_value_type, E>{std::invoke(std::forward<F>(f), **this)};
        }
        return expected_t<new_value_type, E>{error()};
    }

    // map_error: Transform error value
    template <typename F>
    auto map_error(F&& f) const
    {
        using new_error_type = std::invoke_result_t<F, const E&>;
        if (has_value())
        {
            return expected_t<T, new_error_type>{**this};
        }
        return expected_t<T, new_error_type>{std::invoke(std::forward<F>(f), error())};
    }

    // and_then: Chain expected operations (flatmap)
    template <typename F>
    auto and_then(F&& f) const
    {
        if (has_value())
        {
            return std::invoke(std::forward<F>(f), **this);
        }
        using result_type = std::invoke_result_t<F, const T&>;
        return result_type{error()};
    }

    // or_else: Handle error by returning a new expected
    template <typename F>
    auto or_else(F&& f) const
    {
        if (has_value())
        {
            return expected_t{**this};
        }
        return std::invoke(std::forward<F>(f), error());
    }

    // value_or: Unwrap with default on error (C++23 compatible)
    T value_or(T default_val) const
    {
        return has_value() ? **this : std::move(default_val);
    }

    // value_or_else: Unwrap with computed default on error
    template <typename F>
    T value_or_else(F&& f) const
    {
        return has_value() ? **this : std::invoke(std::forward<F>(f), error());
    }
};

} // namespace pkr::units
