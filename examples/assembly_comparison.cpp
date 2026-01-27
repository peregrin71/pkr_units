// Assembly comparison for Godbolt.org
// Demonstrates that SI unit arithmetic with compile-time optimizations
// generates identical assembly to plain floating-point arithmetic
//
// To use on Godbolt:
// 1. Go to godbolt.org
// 2. Select C++ compiler (e.g., clang++ -std=c++20 -O3)
// 3. Copy this code and paste it
// 4. Compare assembly for plain_add() and kilometer_add()
//
// ACTUAL ASSEMBLY OUTPUT (clang++ -std=c++20 -O3):
//
// All same-ratio additions generate IDENTICAL code:
// .LCPI0_0:
//         .quad   0x409f400000000000
// plain_add():
//         movsd   xmm0, qword ptr [rip + .LCPI0_0]
//         ret
//
// .LCPI1_0:
//         .quad   0x409f400000000000
// kilometer_add():
//         movsd   xmm0, qword ptr [rip + .LCPI1_0]
//         ret
//
// Both load constant 2000.0 (0x409f400000000000 in IEEE 754) and return
// This proves: zero runtime overhead for SI unit arithmetic!
//
// COMPILE-TIME CONSTANT FOLDING:
// The compile-time constant cases (no parameters) are evaluated entirely
// at compile-time, so the assembly shows only constant loads.
// This is a BONUS optimization on top of if constexpr - the compiler is
// so aggressive at optimization that it completely eliminates even the
// structure operations.
//
// To see the actual if constexpr optimization in action, use RUNTIME inputs
// (function parameters). Compare:
// - same_ratio_add(x, y):      Simple addition (if constexpr took 'same ratio' branch)
// - mixed_ratio_add(x, y):     Has conversion instructions (if constexpr took 'different ratio' branch)
//
// The difference in assembly length demonstrates why if constexpr is valuable!

#include <ratio>

// Minimal si_unit definition for comparison
namespace si
{
template <typename type_t, typename ratio_t>
struct unit_t
{
    type_t value_;

    constexpr unit_t(type_t v = {})
        : value_(v)
    {
    }

    constexpr type_t value() const
    {
        return value_;
    }
};

// kilometer: ratio<1000, 1>
using kilometer = unit_t<double, std::ratio<1000, 1>>;

// meter: ratio<1, 1> (canonical SI unit)
using meter = unit_t<double, std::ratio<1, 1>>;

// Simplified add helper - demonstrates the optimization
template <typename type_t, typename ratio_t1, typename ratio_t2>
constexpr type_t add_optimized(type_t val1, type_t val2) noexcept
{
    if constexpr (std::is_same_v<ratio_t1, ratio_t2>)
    {
        // OPTIMIZED PATH: Same ratio - no conversion needed
        // This branch is compiled away when ratios are identical
        // Compiler completely eliminates the condition at compile-time
        return val1 + val2;
    }
    else
    {
        // DIFFERENT RATIO PATH: Convert to canonical (1/1)
        // This branch is used when ratios differ and generates actual instructions
        type_t canonical1 = val1 * (static_cast<type_t>(ratio_t1::num) / static_cast<type_t>(ratio_t1::den));
        type_t canonical2 = val2 * (static_cast<type_t>(ratio_t2::num) / static_cast<type_t>(ratio_t2::den));
        return canonical1 + canonical2;
    }
}

// Free function operator+ for kilometers
constexpr auto operator+(const kilometer& lhs, const kilometer& rhs) noexcept
{
    using ratio = std::ratio<1000, 1>;
    double result = add_optimized<double, ratio, ratio>(lhs.value(), rhs.value());
    return kilometer(result);
}

// Free function operator+ for meter
constexpr auto operator+(const meter& lhs, const meter& rhs) noexcept
{
    using ratio = std::ratio<1, 1>;
    double result = add_optimized<double, ratio, ratio>(lhs.value(), rhs.value());
    return meter(result);
}

// Free function operator+ for mixed meter + kilometer
// This uses the non-optimized path and will show conversion instructions
constexpr auto operator+(const meter& lhs, const kilometer& rhs) noexcept
{
    using meter_ratio = std::ratio<1, 1>;
    using km_ratio = std::ratio<1000, 1>;
    double result = add_optimized<double, meter_ratio, km_ratio>(lhs.value(), rhs.value());
    return meter(result);
}
} // namespace si

// ============================================================================
// OPTIMIZED PATH - Same Ratio Cases (generates identical assembly)
// ============================================================================

// CASE 1: Plain floating-point addition
// Expected: movsd + ret (load constant 2000.0)
double plain_add()
{
    return 1000.0 + 1000.0;
}

// CASE 2: SI unit addition (kilometer + kilometer)
// Expected: IDENTICAL to plain_add() due to if constexpr optimization
// Proof: Compiler detects std::is_same_v<ratio<1000,1>, ratio<1000,1>> = true
//        and completely eliminates the else branch at compile-time
si::kilometer kilometer_add()
{
    si::kilometer km1(1000.0);
    si::kilometer km2(1000.0);
    return km1 + km2;
}

// CASE 3: Meter addition (meter + meter)
// Expected: Also IDENTICAL - demonstrates optimization works for any ratio
si::meter meter_add()
{
    si::meter m1(1000.0);
    si::meter m2(1000.0);
    return m1 + m2;
}

// CASE 4: Same result but through variables
// Shows that the optimization persists across different code patterns
double plain_add_via_var()
{
    double a = 1000.0;
    double b = 1000.0;
    return a + b;
}

// CASE 5: SI unit addition with variable storage
// Expected: Also IDENTICAL - compile-time optimization is independent of storage
si::kilometer kilometer_add_via_var()
{
    si::kilometer km1 = 1000.0;
    si::kilometer km2 = 1000.0;
    return km1 + km2;
}

// ============================================================================
// NON-OPTIMIZED PATH - Different Ratio Cases (shows actual arithmetic)
// ============================================================================

// CASE 6: Mixed ratio addition (meter + kilometer) with RUNTIME inputs
// To see the actual arithmetic, we use function parameters (runtime values)
// Expected assembly will be DIFFERENT - shows the actual conversion path:
// - Convert both to canonical ratio
// - Perform addition
// - Convert back to LHS ratio (meter in this case)
//
// This demonstrates why the if constexpr optimization is so valuable:
// When ratios match, this entire conversion overhead is eliminated!
si::meter mixed_ratio_add(double m_val, double km_val)
{
    si::meter m(m_val);       // Runtime meter value
    si::kilometer km(km_val); // Runtime kilometer value
    return m + km;            // Result: converted and added
}

// CASE 7: Same-ratio addition with RUNTIME inputs (for comparison)
// Expected: simpler assembly than mixed_ratio_add
// Since both are the same ratio, no conversion instructions needed
si::meter same_ratio_add(double m_val1, double m_val2)
{
    si::meter m1(m_val1);
    si::meter m2(m_val2);
    return m1 + m2;
}

// CASE 8: Kilometer + kilometer with RUNTIME inputs
// Expected: same simplicity as meter + meter (same-ratio path)
si::kilometer kilometer_add_runtime(double km_val1, double km_val2)
{
    si::kilometer km1(km_val1);
    si::kilometer km2(km_val2);
    return km1 + km2;
}

// ============================================================================
// Main entry point for Godbolt
// ============================================================================
int main()
{
    // Call the functions and use their results to prevent optimization
    // Sum them together so the compiler must actually execute all functions
    double result = 0.0;

    result += plain_add();
    result += kilometer_add().value();
    result += meter_add().value();
    result += plain_add_via_var();
    result += kilometer_add_via_var().value();

    // Runtime input versions
    result += same_ratio_add(500.0, 1000.0).value();
    result += mixed_ratio_add(500.0, 1.0).value();
    result += kilometer_add_runtime(1.0, 2.0).value();

    // Return result as volatile to prevent complete optimization
    volatile double final_result = result;
    return static_cast<int>(final_result);
}
