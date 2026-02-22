#include <gtest/gtest.h>
#include <pkr_units/units/base/amount.h>
#include <pkr_units/units/computer_science/bytes.h>

using namespace ::testing;

class SiAmountOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations: Addition/Subtraction (Same Dimension, Different Ratios)
// ============================================================================

TEST_F(SiAmountOperatorsTest, add_moles)
{
    pkr::units::mole_t<double> mol1{3.0};
    pkr::units::mole_t<double> mol2{2.0};
    auto result = mol1 + mol2;
    static_assert(std::is_same_v<decltype(result), pkr::units::mole_t<double>>);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiAmountOperatorsTest, add_millimole_to_mole)
{
    pkr::units::millimole_t<double> mmol{500.0};
    pkr::units::mole_t<double> mol{1.0};
    auto result = mmol + mol; // preserves LHS (millimole)

    static_assert(std::is_same_v<decltype(result), pkr::units::millimole_t<double>>, "operator+ should preserve LHS type (millimole)");
    // 500 mmol + 1000 mmol = 1500 mmol
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiAmountOperatorsTest, add_mole_to_millimole)
{
    pkr::units::mole_t<double> mol{1.0};
    pkr::units::millimole_t<double> mmol{500.0};
    auto result = mol + mmol;
    static_assert(std::is_same_v<decltype(result), pkr::units::mole_t<double>>);
    // Result is in LHS unit (mole), so 500mmol = 0.5mol, result = 1.5mol
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiAmountOperatorsTest, subtract_moles)
{
    pkr::units::mole_t<double> mol1{5.0};
    pkr::units::mole_t<double> mol2{2.0};
    auto result = mol1 - mol2;
    static_assert(std::is_same_v<decltype(result), pkr::units::mole_t<double>>);
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiAmountOperatorsTest, subtract_millimole_from_mole)
{
    pkr::units::mole_t<double> mol{1.0};
    pkr::units::millimole_t<double> mmol{500.0};
    auto result = mol - mmol;
    static_assert(std::is_same_v<decltype(result), pkr::units::mole_t<double>>);
    // 1mol - 500mmol = 1000mmol - 500mmol = 500mmol = 0.5mol
    ASSERT_DOUBLE_EQ(result.value(), 0.5);
}

TEST_F(SiAmountOperatorsTest, subtract_mole_from_millimole)
{
    pkr::units::millimole_t<double> mmol{1500.0};
    pkr::units::mole_t<double> mol{1.0};
    auto result = mmol - mol; // preserves LHS (millimole)

    static_assert(std::is_same_v<decltype(result), pkr::units::millimole_t<double>>, "operator- should preserve LHS type (millimole)");
    // 1500 mmol - 1000 mmol = 500 mmol
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Multiplication/Division by Scalar
// ============================================================================

TEST_F(SiAmountOperatorsTest, multiply_mole_by_scalar)
{
    pkr::units::mole_t<double> mol{5.0};
    auto result = mol * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiAmountOperatorsTest, divide_mole_by_scalar)
{
    pkr::units::mole_t<double> mol{10.0};
    auto result = mol / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiAmountOperatorsTest, multiply_mole_by_zero)
{
    pkr::units::mole_t<double> mol{5.0};
    auto result = mol * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(SiAmountOperatorsTest, multiply_mole_by_fraction)
{
    pkr::units::mole_t<double> mol{6.0};
    auto result = mol * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

// ============================================================================
// Comparison Operators
// ============================================================================

TEST_F(SiAmountOperatorsTest, equal_moles)
{
    pkr::units::mole_t<double> mol1{5.0};
    pkr::units::mole_t<double> mol2{5.0};
    ASSERT_TRUE(mol1 == mol2);
}

TEST_F(SiAmountOperatorsTest, not_equal_moles)
{
    pkr::units::mole_t<double> mol1{5.0};
    pkr::units::mole_t<double> mol2{3.0};
    ASSERT_TRUE(mol1 != mol2);
}

TEST_F(SiAmountOperatorsTest, less_than_moles)
{
    pkr::units::mole_t<double> mol1{3.0};
    pkr::units::mole_t<double> mol2{5.0};
    ASSERT_TRUE(mol1 < mol2);
}

TEST_F(SiAmountOperatorsTest, less_than_or_equal_moles)
{
    pkr::units::mole_t<double> mol1{5.0};
    pkr::units::mole_t<double> mol2{5.0};
    ASSERT_TRUE(mol1 <= mol2);
}

TEST_F(SiAmountOperatorsTest, greater_than_moles)
{
    pkr::units::mole_t<double> mol1{5.0};
    pkr::units::mole_t<double> mol2{3.0};
    ASSERT_TRUE(mol1 > mol2);
}

TEST_F(SiAmountOperatorsTest, greater_than_or_equal_moles)
{
    pkr::units::mole_t<double> mol1{5.0};
    pkr::units::mole_t<double> mol2{5.0};
    ASSERT_TRUE(mol1 >= mol2);
}

// ============================================================================
// Constexpr Operations
// ============================================================================

TEST_F(SiAmountOperatorsTest, constexpr_mole_addition)
{
    constexpr pkr::units::mole_t<double> mol1{3.0};
    constexpr pkr::units::mole_t<double> mol2{2.0};
    constexpr auto result = mol1 + mol2;
    static_assert(result.value() == 5.0);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiAmountOperatorsTest, constexpr_mole_multiplication_and_division)
{
    constexpr pkr::units::mole_t<double> mol{10.0};
    constexpr auto multiplied = mol * 2.0;
    constexpr auto divided = multiplied / 5.0;
    static_assert(divided.value() == 4.0);
    ASSERT_DOUBLE_EQ(divided.value(), 4.0);
}
