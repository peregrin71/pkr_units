// ============================================================================
// Tests for Matrix Storage Policies
// ============================================================================

#include <gtest/gtest.h>
#include <pkr_units/pkr_units.h>

using namespace pkr::units;
using namespace pkr::units::literals;

// ============================================================================
// Test: Stack Storage (Default)
// ============================================================================

TEST(StackStoragePolicy, DefaultConstruction)
{
    stack_storage<double> storage;
    EXPECT_EQ(storage.get(0, 0), 0.0);
    EXPECT_EQ(storage.get(3, 3), 0.0);
}

TEST(StackStoragePolicy, GetAndSetValues)
{
    stack_storage<int> storage;

    storage.get(0, 0) = 42;
    storage.get(2, 3) = 99;

    EXPECT_EQ(storage.get(0, 0), 42);
    EXPECT_EQ(storage.get(2, 3), 99);
}

TEST(StackStoragePolicy, BracketOperator)
{
    stack_storage<double> storage;

    storage[0][0] = 1.5;
    storage[3][3] = 2.5;

    EXPECT_EQ(storage[0][0], 1.5);
    EXPECT_EQ(storage[3][3], 2.5);
}

TEST(StackStoragePolicy, ConstAccess)
{
    const stack_storage<int> storage;

    // Should compile and not modify
    int val = storage.get(0, 0);
    EXPECT_EQ(val, 0);

    auto& row = storage[0];
    EXPECT_EQ(row[0], 0);
}

TEST(StackStoragePolicy, MultipleInstances)
{
    stack_storage<int> s1;
    stack_storage<int> s2;

    s1.get(0, 0) = 100;
    s2.get(0, 0) = 200;

    // Instances should be independent
    EXPECT_EQ(s1.get(0, 0), 100);
    EXPECT_EQ(s2.get(0, 0), 200);
}

// ============================================================================
// Test: Arena Storage Basic Functionality
// ============================================================================

TEST(ArenaStoragePolicy, DefaultConstruction)
{
    using ArenaType = arena_storage<double, 5>;
    ArenaType::reset_statistics();

    ArenaType arena;
    EXPECT_EQ(arena.get(0, 0), 0.0);
}

TEST(ArenaStoragePolicy, PoolAllocation)
{
    using ArenaType = arena_storage<int, 3>;
    ArenaType::reset_statistics();

    {
        ArenaType a1;
        EXPECT_EQ(ArenaType::active_slots(), 1);

        ArenaType a2;
        EXPECT_EQ(ArenaType::active_slots(), 2);

        ArenaType a3;
        EXPECT_EQ(ArenaType::active_slots(), 3);
    }

    EXPECT_EQ(ArenaType::active_slots(), 0);
}

TEST(ArenaStoragePolicy, PoolExhaustion)
{
    using ArenaType = arena_storage<double, 2>;
    ArenaType::reset_statistics();

    ArenaType a1; // Uses arena slot 0
    ArenaType a2; // Uses arena slot 1

    // This should fall back to stack
    ArenaType a3;
    EXPECT_TRUE(ArenaType::get_fallback_count() > 0);
}

TEST(ArenaStoragePolicy, GetAndSetValues)
{
    using ArenaType = arena_storage<int, 5>;
    ArenaType::reset_statistics();

    ArenaType arena;

    arena.get(0, 0) = 42;
    arena.get(3, 3) = 99;

    EXPECT_EQ(arena.get(0, 0), 42);
    EXPECT_EQ(arena.get(3, 3), 99);
}

TEST(ArenaStoragePolicy, BracketOperator)
{
    using ArenaType = arena_storage<double, 5>;
    ArenaType::reset_statistics();

    ArenaType arena;

    arena[0][0] = 1.5;
    arena[2][2] = 2.5;

    EXPECT_EQ(arena[0][0], 1.5);
    EXPECT_EQ(arena[2][2], 2.5);
}

TEST(ArenaStoragePolicy, ConstAccess)
{
    using ArenaType = arena_storage<int, 5>;
    ArenaType::reset_statistics();

    const ArenaType arena;
    int val = arena.get(0, 0);
    EXPECT_EQ(val, 0);
}

// ============================================================================
// Test: Arena Storage - RAII Semantics
// ============================================================================

TEST(ArenaStoragePolicy, DestructionFreesSlot)
{
    using ArenaType = arena_storage<double, 2>;
    ArenaType::reset_statistics();

    {
        ArenaType a1;
        EXPECT_EQ(ArenaType::active_slots(), 1);
    }

    // Destructor should have freed the slot
    EXPECT_EQ(ArenaType::active_slots(), 0);
}

TEST(ArenaStoragePolicy, SlotReuse)
{
    using ArenaType = arena_storage<int, 1>;
    ArenaType::reset_statistics();

    {
        ArenaType a1;
        a1.get(0, 0) = 100;
        EXPECT_EQ(ArenaType::active_slots(), 1);
    }

    EXPECT_EQ(ArenaType::active_slots(), 0);

    // Allocate again — should reuse the freed slot
    ArenaType a2;
    EXPECT_EQ(ArenaType::active_slots(), 1);
    EXPECT_EQ(a2.get(0, 0), 0); // Fresh allocation
}

// ============================================================================
// Test: Arena Storage - Move Semantics
// ============================================================================

TEST(ArenaStoragePolicy, MoveConstructor)
{
    using ArenaType = arena_storage<int, 5>;
    ArenaType::reset_statistics();

    ArenaType a1;
    a1.get(0, 0) = 42;

    // Move to a2 — should transfer arena ownership
    ArenaType a2 = std::move(a1);

    EXPECT_EQ(a2.get(0, 0), 42);
    EXPECT_EQ(ArenaType::active_slots(), 1); // Still one slot in use
}

TEST(ArenaStoragePolicy, MoveAssignment)
{
    using ArenaType = arena_storage<int, 5>;
    ArenaType::reset_statistics();

    ArenaType a1;
    a1.get(0, 0) = 42;

    ArenaType a2;
    a2.get(0, 0) = 99;

    // Move a1 into a2
    a2 = std::move(a1);

    EXPECT_EQ(a2.get(0, 0), 42);
    EXPECT_EQ(ArenaType::active_slots(), 2); // Both a1 and a2 (now invalid)
}

TEST(ArenaStoragePolicy, FallbackToStackOnMove)
{
    using ArenaType = arena_storage<int, 1>;
    ArenaType::reset_statistics();

    ArenaType a1;
    a1.get(0, 0) = 100;

    // a1 is using arena
    EXPECT_TRUE(a1.using_arena);

    // Move to a2
    ArenaType a2 = std::move(a1);

    // a2 should own the arena slot
    EXPECT_TRUE(a2.using_arena);
    EXPECT_EQ(a2.get(0, 0), 100);
}

// ============================================================================
// Test: Arena Storage - Statistics
// ============================================================================

TEST(ArenaStoragePolicy, PeakUsageTracking)
{
    using ArenaType = arena_storage<double, 5>;
    ArenaType::reset_statistics();

    EXPECT_EQ(ArenaType::get_peak_usage(), 0);

    {
        ArenaType a1;
        EXPECT_EQ(ArenaType::get_peak_usage(), 1);

        {
            ArenaType a2;
            EXPECT_EQ(ArenaType::get_peak_usage(), 2);
        }

        // Still only 1 active, but peak was 2
        EXPECT_EQ(ArenaType::active_slots(), 1);
        EXPECT_EQ(ArenaType::get_peak_usage(), 2);
    }
}

TEST(ArenaStoragePolicy, FallbackCountTracking)
{
    using ArenaType = arena_storage<int, 1>;
    ArenaType::reset_statistics();

    EXPECT_EQ(ArenaType::get_fallback_count(), 0);

    ArenaType a1;
    EXPECT_EQ(ArenaType::get_fallback_count(), 0);

    // This should trigger fallback
    ArenaType a2;
    EXPECT_EQ(ArenaType::get_fallback_count(), 1);

    // Another fallback
    ArenaType a3;
    EXPECT_EQ(ArenaType::get_fallback_count(), 2);
}

TEST(ArenaStoragePolicy, ResetStatistics)
{
    using ArenaType = arena_storage<double, 5>;

    {
        ArenaType a1;
        EXPECT_GT(ArenaType::get_peak_usage(), 0);
    }

    ArenaType::reset_statistics();

    EXPECT_EQ(ArenaType::get_peak_usage(), 0);
    EXPECT_EQ(ArenaType::get_fallback_count(), 0);
}

// ============================================================================
// Test: Custom Exhaustion Policy
// ============================================================================

struct CountingPolicy
{
    static inline int call_count = 0;

    static void on_exhausted()
    {
        ++call_count;
    }
};

TEST(ArenaStoragePolicy, CustomExhaustionPolicy)
{
    using ArenaType = arena_storage<int, 2, CountingPolicy>;
    CountingPolicy::call_count = 0;
    ArenaType::reset_statistics();

    ArenaType a1;
    ArenaType a2;

    EXPECT_EQ(CountingPolicy::call_count, 0);

    // This should call the policy
    ArenaType a3;
    EXPECT_EQ(CountingPolicy::call_count, 1);

    // Another fallback
    ArenaType a4;
    EXPECT_EQ(CountingPolicy::call_count, 2);
}

// ============================================================================
// Test: Integration with Matrix Types
// ============================================================================

TEST(MatrixStorageIntegration, DefaultStackStorageBackwardCompatible)
{
    // Should use stack storage by default
    matrix_4d_units_t<meter_t> m1 = matrix_4d_units_t<meter_t>::identity_4d();
    matrix_4d_units_t<meter_t> m2 = matrix_4d_units_t<meter_t>::identity_4d();

    // Should be able to multiply
    auto result = m1 * m2;

    // Result should be identity
    for (std::size_t i = 0; i < 4; ++i)
    {
        for (std::size_t j = 0; j < 4; ++j)
        {
            if (i == j)
            {
                EXPECT_EQ(result(i, j).value(), 1.0);
            }
            else
            {
                EXPECT_EQ(result(i, j).value(), 0.0);
            }
        }
    }
}

TEST(MatrixStorageIntegration, ExplicitArenaStorage)
{
    using MatrixWithArena = matrix_4d_units_t<meter_t, arena_storage<meter_t, 5>>;

    arena_storage<meter_t, 5>::reset_statistics();

    MatrixWithArena m1 = MatrixWithArena::identity_4d();
    MatrixWithArena m2 = MatrixWithArena::identity_4d();

    EXPECT_EQ(arena_storage<meter_t, 5>::active_slots(), 2);

    auto result = m1 * m2;

    // Check identity
    EXPECT_EQ(result(0, 0).value(), 1.0);
    EXPECT_EQ(result(1, 1).value(), 1.0);
}

TEST(MatrixStorageIntegration, ArenaExhaustionWithMatrices)
{
    using MatrixWithArena = matrix_4d_units_t<meter_t, arena_storage<meter_t, 2>>;

    arena_storage<meter_t, 2>::reset_statistics();

    MatrixWithArena m1 = MatrixWithArena::identity_4d();
    MatrixWithArena m2 = MatrixWithArena::identity_4d();

    EXPECT_EQ(arena_storage<meter_t, 2>::get_fallback_count(), 0);

    // This should fall back to stack
    MatrixWithArena m3 = MatrixWithArena::identity_4d();

    EXPECT_GT(arena_storage<meter_t, 2>::get_fallback_count(), 0);
}

TEST(MatrixStorageIntegration, MeasurementMatrixWithArena)
{
    using MatrixType = matrix_measurement_rss_4d_t<meter_t, arena_storage<measurement_rss_t<meter_t>, 3>>;

    auto m = measurement_rss_t<meter_t>{5_m, 0.1_m};

    MatrixType mat1;
    mat1(0, 0) = m;

    EXPECT_EQ(mat1(0, 0).value().value(), 5.0);
}

// ============================================================================
// Test: PoolSize Compile-Time Information
// ============================================================================

TEST(ArenaStoragePolicy, PoolSizeCompileTime)
{
    EXPECT_EQ((arena_storage<int, 5>::pool_size()), 5);
    EXPECT_EQ((arena_storage<int, 10>::pool_size()), 10);
    EXPECT_EQ((arena_storage<int, 1>::pool_size()), 1);
}

// ============================================================================
// Test: Different Value Types
// ============================================================================

TEST(ArenaStoragePolicy, IntValueType)
{
    using ArenaType = arena_storage<int, 3>;
    ArenaType::reset_statistics();

    ArenaType arena;
    arena.get(0, 0) = 42;
    EXPECT_EQ(arena.get(0, 0), 42);
}

TEST(ArenaStoragePolicy, DoubleValueType)
{
    using ArenaType = arena_storage<double, 3>;
    ArenaType::reset_statistics();

    ArenaType arena;
    arena.get(0, 0) = 3.14159;
    EXPECT_DOUBLE_EQ(arena.get(0, 0), 3.14159);
}

TEST(ArenaStoragePolicy, UnitTypeValueType)
{
    using ArenaType = arena_storage<meter_t, 3>;
    ArenaType::reset_statistics();

    ArenaType arena;
    arena.get(0, 0) = meter_t{5.0};
    EXPECT_EQ(arena.get(0, 0).value(), 5.0);
}

// ============================================================================
// Test: Stress Test - Many Allocations
// ============================================================================

TEST(ArenaStoragePolicy, StressTestManyAllocations)
{
    using ArenaType = arena_storage<int, 10>;
    ArenaType::reset_statistics();

    // Create and destroy many times
    for (int i = 0; i < 100; ++i)
    {
        {
            ArenaType a;
            a.get(0, 0) = i;
        }
    }

    // All should have been cleaned up
    EXPECT_EQ(ArenaType::active_slots(), 0);
}

TEST(ArenaStoragePolicy, StressTestNestedAllocations)
{
    using ArenaType = arena_storage<double, 5>;
    ArenaType::reset_statistics();

    {
        ArenaType a1;
        {
            ArenaType a2;
            {
                ArenaType a3;
                {
                    ArenaType a4;
                    {
                        ArenaType a5;
                        EXPECT_EQ(ArenaType::active_slots(), 5);
                    }
                    EXPECT_EQ(ArenaType::active_slots(), 4);
                }
                EXPECT_EQ(ArenaType::active_slots(), 3);
            }
            EXPECT_EQ(ArenaType::active_slots(), 2);
        }
        EXPECT_EQ(ArenaType::active_slots(), 1);
    }
    EXPECT_EQ(ArenaType::active_slots(), 0);
}
