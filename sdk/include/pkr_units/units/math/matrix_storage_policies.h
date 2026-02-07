#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <array>
#include <bitset>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Matrix Storage Policies
// ============================================================================
//
// The matrix_4d_units_t and matrix_measurement_rss_4d_t classes use a storage
// policy pattern to support different allocation strategies:
//
// 1. stack_storage (default)
//    - Allocates 128 bytes per matrix instance on the stack
//    - Zero overhead, backward compatible
//    - Suitable for most use cases
//
// 2. arena_storage
//    - Pre-allocates a fixed pool of matrices
//    - Automatically falls back to stack if pool is exhausted
//    - Perfect for stack-limited embedded systems
//    - Provides runtime monitoring (peak_usage, fallback_count)
//
// USAGE EXAMPLES:
//
//   // Default (stack): 128 bytes per instance
//   matrix_4d_units_t<meter_t> m1;
//
//   // Arena-based: pool of 10, falls back to stack
//   matrix_4d_units_t<meter_t, arena_storage<meter_t, 10>> m2;
//
//   // Custom policy for monitoring
//   matrix_4d_units_t<meter_t,
//       arena_storage<meter_t, 10, my_exhausted_policy>> m3;
//
// EMBEDDED SYSTEMS GUIDANCE:
//
//   For stack-limited systems (e.g., ARM Cortex-M with 4-16 KB stack):
//
//   1. During development, use arena_storage with generous pool size
//   2. Monitor fallback_count to detect pool exhaustion
//   3. Monitor peak_usage to find optimal pool size
//   4. Use reset_statistics() before running scenarios
//
//   Example test code:
//     void calibrate_pool_size() {
//         arena_storage<meter_t>::reset_statistics();
//         // Run your algorithms...
//         size_t needed = arena_storage<meter_t>::get_peak_usage();
//         printf("Set POOL_SIZE to at least %zu\\n", needed + 1);
//     }

// ============================================================================
// Default policy: silently degrade to stack when arena exhausted
// ============================================================================
struct default_arena_policy
{
    // Called when arena pool is exhausted
    // Default: silent fallback to stack allocation
    static void on_exhausted()
    {
        // Silent fallback to stack allocation
    }
};

// ============================================================================
// Stack-based storage policy (default, zero overhead)
// ============================================================================
template <typename T>
struct stack_storage
{
    using value_type = T;
    using array_type = std::array<std::array<T, 4>, 4>;

    array_type data{};

    constexpr T& get(std::size_t row, std::size_t col)
    {
        return data[row][col];
    }

    constexpr const T& get(std::size_t row, std::size_t col) const
    {
        return data[row][col];
    }

    constexpr std::array<T, 4>& operator[](std::size_t row)
    {
        return data[row];
    }

    constexpr const std::array<T, 4>& operator[](std::size_t row) const
    {
        return data[row];
    }
};

// ============================================================================
// Arena-based storage policy (for stack-limited embedded systems)
// ============================================================================
//
// Allocates from a fixed-size pool by default, gracefully falling back to
// stack allocation if the pool is exhausted.
//
// Template Parameters:
//   T              - Element type (e.g., meter_t, measurement_rss_t<meter_t>)
//   POOL_SIZE      - Maximum number of matrices in the arena (default: 10)
//   ExhaustedPolicy - Called when pool is full (default: silent fallback)
//
// Monitoring Methods:
//   peak_usage()        - Highest simultaneous allocations seen
//   fallback_count()    - Number of times pool exhaustion triggered fallback
//   active_slots()      - Currently allocated arena slots
//   reset_statistics()  - Clear peak_usage and fallback_count
//
// Example:
//   struct my_policy {
//       static void on_exhausted() {
//           log_warning("Matrix arena exhausted, falling back to stack");
//       }
//   };
//
//   using MyMatrix = matrix_4d_units_t<meter_t,
//       arena_storage<meter_t, 20, my_policy>>;
//
template <typename T, std::size_t POOL_SIZE = 10, typename ExhaustedPolicy = default_arena_policy>
struct arena_storage
{
    using value_type = T;
    using array_type = std::array<std::array<T, 4>, 4>;

    static_assert(POOL_SIZE > 0, "POOL_SIZE must be greater than 0");

    std::size_t arena_index;
    array_type stack_fallback{};
    bool using_arena;

    // Monitoring statistics
    static inline std::size_t peak_usage = 0;
    static inline std::size_t fallback_count = 0;

private:
    static inline std::array<array_type, POOL_SIZE> s_pool{};
    static inline std::bitset<POOL_SIZE> s_in_use{};

public:
    arena_storage()
        : arena_index(POOL_SIZE)
        , using_arena(false)
    {
        // Try to allocate from arena
        for (std::size_t i = 0; i < POOL_SIZE; ++i)
        {
            if (!s_in_use[i])
            {
                arena_index = i;
                s_in_use[i] = true;
                using_arena = true;
                peak_usage = std::max(peak_usage, static_cast<std::size_t>(s_in_use.count()));
                return;
            }
        }

        // Arena exhausted — notify policy and fall back to stack
        ExhaustedPolicy::on_exhausted();
        ++fallback_count;
        using_arena = false;
    }

    ~arena_storage()
    {
        if (using_arena && arena_index < POOL_SIZE)
        {
            s_in_use[arena_index] = false;
        }
    }

    // Prevent copying (each instance owns its slot)
    arena_storage(const arena_storage&) = delete;
    arena_storage& operator=(const arena_storage&) = delete;

    // Allow moving
    arena_storage(arena_storage&& other) noexcept
        : arena_index(other.arena_index)
        , using_arena(other.using_arena)
    {
        if (using_arena)
        {
            other.using_arena = false; // Mark moved-from as invalid
        }
        else
        {
            stack_fallback = std::move(other.stack_fallback);
        }
    }

    arena_storage& operator=(arena_storage&& other) noexcept
    {
        if (this != &other)
        {
            if (using_arena && arena_index < POOL_SIZE)
            {
                s_in_use[arena_index] = false;
            }
            arena_index = other.arena_index;
            using_arena = other.using_arena;
            if (!using_arena)
            {
                stack_fallback = std::move(other.stack_fallback);
                other.using_arena = false;
            }
        }
        return *this;
    }

    T& get(std::size_t row, std::size_t col)
    {
        return using_arena ? s_pool[arena_index][row][col] : stack_fallback[row][col];
    }

    const T& get(std::size_t row, std::size_t col) const
    {
        return using_arena ? s_pool[arena_index][row][col] : stack_fallback[row][col];
    }

    std::array<T, 4>& operator[](std::size_t row)
    {
        return using_arena ? s_pool[arena_index][row] : stack_fallback[row];
    }

    const std::array<T, 4>& operator[](std::size_t row) const
    {
        return using_arena ? s_pool[arena_index][row] : stack_fallback[row];
    }

    // ========== Monitoring Utilities ==========

    static constexpr std::size_t pool_size()
    {
        return POOL_SIZE;
    }

    static std::size_t active_slots()
    {
        return s_in_use.count();
    }

    static std::size_t get_peak_usage()
    {
        return peak_usage;
    }

    static std::size_t get_fallback_count()
    {
        return fallback_count;
    }

    static void reset_statistics()
    {
        peak_usage = 0;
        fallback_count = 0;
    }
};

} // namespace PKR_UNITS_NAMESPACE
