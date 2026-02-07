// ============================================================================
// Matrix Storage Policies Example
// ============================================================================
//
// This example demonstrates the matrix storage policies for handling
// different memory allocation strategies in embedded systems.
//
// Key concepts:
// 1. Default stack-based storage (zero overhead)
// 2. Arena-based storage with graceful fallback
// 3. Monitoring and tuning for embedded systems
//

#include <pkr_units/si_units.h>
#include <pkr_units/format/si.h>
#include <iostream>
#include <iomanip>
#include <format>

namespace ex {

using namespace pkr::units;
using namespace pkr::units::literals;

// ============================================================================
// Example 1: Default stack-based storage (backward compatible)
// ============================================================================
void example_default_stack_storage()
{
    std::cout << "\n=== Example 1: Default Stack Storage ===\n";
    
    // Each matrix instance allocates 128 bytes on the stack
    matrix_4d_units_t<meter_t> m1;
    matrix_4d_units_t<meter_t> m2;
    
    // Initialize with identity
    m1 = matrix_4d_units_t<meter_t>::identity_4d();
    m2 = matrix_4d_units_t<meter_t>::identity_4d();
    
    // Perform matrix operations
    auto result = m1 * m2;
    
    std::cout << "Stack storage uses 128 bytes per matrix instance\n";
    std::cout << "Zero runtime overhead, backward compatible\n";
}

// ============================================================================
// Example 2: Arena-based storage (embedded systems)
// ============================================================================
void example_arena_storage()
{
    std::cout << "\n=== Example 2: Arena Storage with Pool ===\n";
    
    // Use arena storage with a pool of 5 matrices
    // If pool is exhausted, automatically falls back to stack
    using MatrixWithArena = matrix_4d_units_t<meter_t, 
                                              arena_storage<meter_t, 5>>;
    
    std::cout << "Created arena storage with pool size: " 
              << arena_storage<meter_t, 5>::pool_size() << "\n";
    
    // Allocate from the arena
    MatrixWithArena m1 = MatrixWithArena::identity_4d();
    MatrixWithArena m2 = MatrixWithArena::identity_4d();
    MatrixWithArena m3 = MatrixWithArena::identity_4d();
    
    std::cout << "Active arena slots: " 
              << arena_storage<meter_t, 5>::active_slots() << "/5\n";
    
    // Another matrix will use arena space
    MatrixWithArena m4 = MatrixWithArena::identity_4d();
    std::cout << "Active arena slots after m4: " 
              << arena_storage<meter_t, 5>::active_slots() << "/5\n";
    
    // Perform operations
    auto result = m1 * m2;
}

// ============================================================================
// Example 3: Handling arena exhaustion with custom policy
// ============================================================================
struct WarningPolicy
{
    static void on_exhausted()
    {
        std::cerr << "WARNING: Matrix arena pool exhausted, "
                  << "falling back to stack allocation\n";
    }
};

void example_custom_exhaustion_policy()
{
    std::cout << "\n=== Example 3: Custom Exhaustion Policy ===\n";
    
    // Use arena storage with custom policy
    using MatrixWithWarning = matrix_4d_units_t<meter_t,
                                                arena_storage<meter_t, 2, WarningPolicy>>;
    
    arena_storage<meter_t, 2, WarningPolicy>::reset_statistics();
    
    // Create 3 matrices — 3rd will trigger exhaustion warning
    std::cout << "Creating 3 matrices with pool size 2...\n";
    MatrixWithWarning m1 = MatrixWithWarning::identity_4d();
    std::cout << "m1: active slots = " 
              << arena_storage<meter_t, 2, WarningPolicy>::active_slots() << "\n";
    
    MatrixWithWarning m2 = MatrixWithWarning::identity_4d();
    std::cout << "m2: active slots = " 
              << arena_storage<meter_t, 2, WarningPolicy>::active_slots() << "\n";
    
    MatrixWithWarning m3 = MatrixWithWarning::identity_4d();  // Falls back to stack
    std::cout << "m3: active slots = " 
              << arena_storage<meter_t, 2, WarningPolicy>::active_slots() << "\n";
    
    std::cout << "Fallback count: " 
              << arena_storage<meter_t, 2, WarningPolicy>::get_fallback_count() << "\n";
}

// ============================================================================
// Example 4: Monitoring and profiling for embedded systems
// ============================================================================
void example_profiling()
{
    std::cout << "\n=== Example 4: Profiling Arena Usage ===\n";
    
    using MatrixProfile = matrix_4d_units_t<meter_t,
                                            arena_storage<meter_t, 10>>;
    
    // Reset statistics before profiling
    arena_storage<meter_t, 10>::reset_statistics();
    
    std::cout << "Running matrix operations for profiling...\n";
    
    // Simulate some algorithm that creates temporary matrices
    for (int iteration = 0; iteration < 3; ++iteration) {
        MatrixProfile temp1 = MatrixProfile::identity_4d();
        MatrixProfile temp2 = MatrixProfile::identity_4d();
        
        // Perform some work
        auto result = temp1 * temp2;
        // temp1 and temp2 destroyed here, freeing arena slots
    }
    
    // Analyze results
    std::size_t peak = arena_storage<meter_t, 10>::get_peak_usage();
    std::size_t fallbacks = arena_storage<meter_t, 10>::get_fallback_count();
    
    std::cout << "\n--- Profiling Results ---\n";
    std::cout << "Peak simultaneous allocations: " << peak << "/10\n";
    std::cout << "Pool exhaustion events: " << fallbacks << "\n";
    std::cout << "Recommended pool size: " << (peak + 1) << "\n";
    
    if (fallbacks == 0) {
        std::cout << "✓ No fallbacks occurred\n";
    } else {
        std::cout << "✗ Increase pool size to handle peak load\n";
    }
}

// ============================================================================
// Example 5: Using arena storage with measurements
// ============================================================================
void example_arena_with_measurements()
{
    std::cout << "\n=== Example 5: Arena Storage with Measurements ===\n";
    
    // Storage policy is for the measurement type, not the base unit
    using MeasurementMatrix = matrix_measurement_rss_4d_t<meter_t,
                                  arena_storage<measurement_rss_t<meter_t>, 3>>;
    
    auto m = measurement_rss_t<meter_t>{5_m, 0.1_m};  // 5 meters +/- 0.1
    
    MeasurementMatrix mat1;
    mat1(0, 0) = m;
    mat1(0, 1) = m;
    
    std::cout << "Arena storage works with measurements too\n";
    std::cout << "Active slots: "
              << arena_storage<measurement_rss_t<meter_t>, 3>::active_slots()
              << "/3\n";
}

// ============================================================================
// Example 6: Optimization guidance
// ============================================================================
void print_optimization_guidance()
{
    std::cout << "\n=== Optimization Guidance ===\n";
    std::cout << R"(
For stack-limited embedded systems:

1. PROFILING PHASE:
   - Use arena_storage with generous pool size (e.g., 20)
   - Run representative workloads
   - Check get_peak_usage() to find actual need

2. TUNING PHASE:
   - Set POOL_SIZE to peak_usage + 1 (buffer for edge cases)
   - Run with custom WarningPolicy to catch fallbacks
   - If fallbacks occur, increase pool size iteratively

3. PRODUCTION PHASE:
   - Use optimized POOL_SIZE from tuning
   - Optional: Remove custom policy for silent operation
   - Monitor stack use with profiling tools

4. STACK CALCULATIONS:
   - Each fallback uses 128 bytes on stack
   - Each arena slot avoids 128 bytes on stack
   - Effective reduction = pool_size × 128 bytes

Example for ARM Cortex-M4 (16 KB stack):
   - With arena_storage<T, 10>: max 1.28 KB temporary matrices
   - Leaves 14.7 KB for function calls and other data
   - Safe for most real-time algorithms
    )";
}

// ============================================================================
// Main entry point
// ================ (remove old main, keep function declarations)
// ============================================================================
void example_memory_bounds_verification()
{
    std::cout << "\n=== Example 9: Memory Bounds Verification ===\n";
    
    using namespace pkr::units;
    using namespace pkr::units::literals;
    
    std::cout << std::format("Stack-allocated matrix size: {} bytes\n", 
                             sizeof(matrix_4d_units_t<pkr::units::meter_t>));
    std::cout << "Arena storage avoids stack allocation for temporary matrices\n";
    std::cout << "Profile your application to find optimal pool size\n";
}

} // namespace ex