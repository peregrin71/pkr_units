#include <gtest/gtest.h>
#include <pkr_units/units/base/amount.h>

using namespace ::testing;
using namespace pkr::units;

static_assert(std::is_same_v<decltype(std::declval<mole_t<double>>() + std::declval<mole_t<double>>()), mole_t<double>>, "Mole addition must return mole_t");
static_assert(std::is_same_v<decltype(std::declval<mole_t<double>>() * 2.0), mole_t<double>>, "Mole scalar multiplication must return mole_t");

class SiAmountTest : public Test
{
};

TEST_F(SiAmountTest, construction_and_access)
{
    pkr::units::mole_t<double> mol{5.0};
    ASSERT_DOUBLE_EQ(mol.value(), 5.0);
    ASSERT_DOUBLE_EQ(*mol, 5.0);
}

TEST_F(SiAmountTest, zero_and_negative_values)
{
    pkr::units::mole_t<double> zero_mol{0.0};
    ASSERT_DOUBLE_EQ(zero_mol.value(), 0.0);

    pkr::units::mole_t<double> neg_mol{-3.5};
    ASSERT_DOUBLE_EQ(neg_mol.value(), -3.5);
}

TEST_F(SiAmountTest, unit_variants)
{
    pkr::units::millimole_t<double> mmol{250.0};
    ASSERT_DOUBLE_EQ(mmol.value(), 250.0);

    pkr::units::micromole_t<double> umol{1000.0};
    ASSERT_DOUBLE_EQ(umol.value(), 1000.0);

    pkr::units::nanomole_t<double> nmol{100.0};
    ASSERT_DOUBLE_EQ(nmol.value(), 100.0);

    pkr::units::kilomole_t<double> kmol{2.5};
    ASSERT_DOUBLE_EQ(kmol.value(), 2.5);
}

TEST_F(SiAmountTest, add_moles)
{
    pkr::units::mole_t<double> mol1{3.0};
    pkr::units::mole_t<double> mol2{2.0};
    auto result = mol1 + mol2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiAmountTest, subtract_moles)
{
    pkr::units::mole_t<double> mol1{5.0};
    pkr::units::mole_t<double> mol2{2.0};
    auto result = mol1 - mol2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiAmountTest, add_millimoles)
{
    pkr::units::millimole_t<double> mmol1{500.0};
    pkr::units::millimole_t<double> mmol2{250.0};
    auto result = mmol1 + mmol2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiAmountTest, subtract_millimoles)
{
    pkr::units::millimole_t<double> mmol1{750.0};
    pkr::units::millimole_t<double> mmol2{250.0};
    auto result = mmol1 - mmol2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiAmountTest, add_mole_to_millimole)
{
    pkr::units::mole_t<double> mol{1.0};
    pkr::units::millimole_t<double> mmol{500.0};
    auto result = mol + mmol;
    // Result is in LHS type (mole)
    // 1mol + 0.5mol = 1.5mol
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiAmountTest, add_millimole_to_mole)
{
    pkr::units::millimole_t<double> mmol{500.0};
    pkr::units::mole_t<double> mol{1.0};
    auto result = mmol + mol;
    // Result is in LHS type (millimole)
    // 500mmol + 1000mmol = 1500mmol
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiAmountTest, subtract_mole_from_millimole)
{
    pkr::units::millimole_t<double> mmol{1500.0};
    pkr::units::mole_t<double> mol{1.0};
    auto result = mmol - mol;
    // Result is in LHS type (millimole)
    // 1500mmol - 1000mmol = 500mmol
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiAmountTest, subtract_millimole_from_mole)
{
    pkr::units::mole_t<double> mol{2.0};
    pkr::units::millimole_t<double> mmol{500.0};
    auto result = mol - mmol;
    // Result is in LHS type (mole)
    // 2mol - 0.5mol = 1.5mol
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

// ============================================================================
// Scalar Multiplication and Division
// ============================================================================

TEST_F(SiAmountTest, multiply_mole_by_scalar)
{
    pkr::units::mole_t<double> mol{2.0};
    auto result = mol * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiAmountTest, divide_mole_by_scalar)
{
    pkr::units::mole_t<double> mol{6.0};
    auto result = mol / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiAmountTest, multiply_millimole_by_scalar)
{
    pkr::units::millimole_t<double> mmol{100.0};
    auto result = mmol * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiAmountTest, divide_millimole_by_scalar)
{
    pkr::units::millimole_t<double> mmol{500.0};
    auto result = mmol / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Amount Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiAmountTest, multiply_mole_by_mole)
{
    pkr::units::mole_t<double> mol1{2.0};
    pkr::units::mole_t<double> mol2{3.0};
    auto result = mol1 * mol2;
    // Result has amount dimension = 2 (mol²)
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.amount, 2);
}

// ============================================================================
// Amount Division (Creates Dimensionless)
// ============================================================================

TEST_F(SiAmountTest, divide_mole_by_mole)
{
    pkr::units::mole_t<double> mol1{10.0};
    pkr::units::mole_t<double> mol2{2.0};
    auto result = mol1 / mol2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.amount, 0);
}

TEST_F(SiAmountTest, divide_millimole_by_millimole)
{
    pkr::units::millimole_t<double> mmol1{500.0};
    pkr::units::millimole_t<double> mmol2{100.0};
    auto result = mmol1 / mmol2;
    // Result is dimensionless
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.amount, 0);
}

// ============================================================================
// Constexpr Tests
// ============================================================================

TEST_F(SiAmountTest, constexpr_mole_addition)
{
    constexpr pkr::units::mole_t<double> mol1{3.0};
    constexpr pkr::units::mole_t<double> mol2{2.0};
    constexpr auto result = mol1 + mol2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiAmountTest, constexpr_mole_multiplication)
{
    constexpr pkr::units::mole_t<double> mol{2.0};
    constexpr auto result = mol * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiAmountTest, very_small_amount_values)
{
    pkr::units::nanomole_t<double> nmol{0.001};
    ASSERT_DOUBLE_EQ(nmol.value(), 0.001);
}

TEST_F(SiAmountTest, very_large_amount_values)
{
    pkr::units::kilomole_t<double> kmol{1000000.0};
    ASSERT_DOUBLE_EQ(kmol.value(), 1000000.0);
}

TEST_F(SiAmountTest, add_very_different_scales)
{
    pkr::units::millimole_t<double> mmol{1.0}; // 1 millimole
    pkr::units::mole_t<double> mol{1.0};       // 1 mole = 1000 mmol
    auto result = mmol + mol;
    // Result is in LHS type (millimole)
    // 1 mmol + 1000 mmol = 1001 mmol
    ASSERT_DOUBLE_EQ(result.value(), 1001.0);
}

TEST_F(SiAmountTest, subtract_resulting_in_negative)
{
    pkr::units::mole_t<double> mol1{1.0};
    pkr::units::mole_t<double> mol2{3.0};
    auto result = mol1 - mol2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}
