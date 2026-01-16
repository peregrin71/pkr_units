// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#include <gtest/gtest.h>
#include <si_units/standard/amount.h>

using namespace ::testing;

class SiAmountTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiAmountTest, mole_construction)
{
    si::mole mol{5.0};
    ASSERT_DOUBLE_EQ(mol.value(), 5.0);
}

TEST_F(SiAmountTest, mole_dereference_operator)
{
    si::mole mol{5.0};
    ASSERT_DOUBLE_EQ(*mol, 5.0);
}

TEST_F(SiAmountTest, mole_zero_value)
{
    si::mole mol{0.0};
    ASSERT_DOUBLE_EQ(mol.value(), 0.0);
}

TEST_F(SiAmountTest, mole_negative_value)
{
    si::mole mol{-3.5};
    ASSERT_DOUBLE_EQ(mol.value(), -3.5);
}

TEST_F(SiAmountTest, millimole_construction)
{
    si::millimole mmol{250.0};
    ASSERT_DOUBLE_EQ(mmol.value(), 250.0);
}

TEST_F(SiAmountTest, micromole_construction)
{
    si::micromole umol{1000.0};
    ASSERT_DOUBLE_EQ(umol.value(), 1000.0);
}

TEST_F(SiAmountTest, nanomole_construction)
{
    si::nanomole nmol{100.0};
    ASSERT_DOUBLE_EQ(nmol.value(), 100.0);
}

TEST_F(SiAmountTest, kilomole_construction)
{
    si::kilomole kmol{2.5};
    ASSERT_DOUBLE_EQ(kmol.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiAmountTest, copy_constructor)
{
    si::mole mol1{5.0};
    si::mole mol2 = mol1;
    ASSERT_DOUBLE_EQ(mol2.value(), 5.0);
}

TEST_F(SiAmountTest, move_constructor)
{
    si::mole mol1{5.0};
    si::mole mol2 = std::move(mol1);
    ASSERT_DOUBLE_EQ(mol2.value(), 5.0);
}

TEST_F(SiAmountTest, copy_assignment)
{
    si::mole mol1{5.0};
    si::mole mol2{0.0};
    mol2 = mol1;
    ASSERT_DOUBLE_EQ(mol2.value(), 5.0);
}

TEST_F(SiAmountTest, move_assignment)
{
    si::mole mol1{5.0};
    si::mole mol2{0.0};
    mol2 = std::move(mol1);
    ASSERT_DOUBLE_EQ(mol2.value(), 5.0);
}

// ============================================================================
// Arithmetic Tests - Same Unit
// ============================================================================

TEST_F(SiAmountTest, add_moles)
{
    si::mole mol1{3.0};
    si::mole mol2{2.0};
    auto result = mol1 + mol2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiAmountTest, subtract_moles)
{
    si::mole mol1{5.0};
    si::mole mol2{2.0};
    auto result = mol1 - mol2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiAmountTest, add_millimoles)
{
    si::millimole mmol1{500.0};
    si::millimole mmol2{250.0};
    auto result = mmol1 + mmol2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiAmountTest, subtract_millimoles)
{
    si::millimole mmol1{750.0};
    si::millimole mmol2{250.0};
    auto result = mmol1 - mmol2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiAmountTest, add_mole_to_millimole)
{
    si::mole mol{1.0};
    si::millimole mmol{500.0};
    auto result = mol + mmol;
    // Result is in LHS type (mole)
    // 1mol + 0.5mol = 1.5mol
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiAmountTest, add_millimole_to_mole)
{
    si::millimole mmol{500.0};
    si::mole mol{1.0};
    auto result = mmol + mol;
    // Result is in LHS type (millimole)
    // 500mmol + 1000mmol = 1500mmol
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiAmountTest, subtract_mole_from_millimole)
{
    si::millimole mmol{1500.0};
    si::mole mol{1.0};
    auto result = mmol - mol;
    // Result is in LHS type (millimole)
    // 1500mmol - 1000mmol = 500mmol
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiAmountTest, subtract_millimole_from_mole)
{
    si::mole mol{2.0};
    si::millimole mmol{500.0};
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
    si::mole mol{2.0};
    auto result = mol * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiAmountTest, divide_mole_by_scalar)
{
    si::mole mol{6.0};
    auto result = mol / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiAmountTest, divide_by_zero_scalar_throws)
{
    si::mole mol{5.0};
    ASSERT_THROW(mol / 0.0, std::invalid_argument);
}

TEST_F(SiAmountTest, multiply_millimole_by_scalar)
{
    si::millimole mmol{100.0};
    auto result = mmol * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiAmountTest, divide_millimole_by_scalar)
{
    si::millimole mmol{500.0};
    auto result = mmol / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Amount Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiAmountTest, multiply_mole_by_mole)
{
    si::mole mol1{2.0};
    si::mole mol2{3.0};
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
    si::mole mol1{10.0};
    si::mole mol2{2.0};
    auto result = mol1 / mol2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.amount, 0);
}

TEST_F(SiAmountTest, divide_millimole_by_millimole)
{
    si::millimole mmol1{500.0};
    si::millimole mmol2{100.0};
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
    constexpr si::mole mol1{3.0};
    constexpr si::mole mol2{2.0};
    constexpr auto result = mol1 + mol2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiAmountTest, constexpr_mole_multiplication)
{
    constexpr si::mole mol{2.0};
    constexpr auto result = mol * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiAmountTest, very_small_amount_values)
{
    si::nanomole nmol{0.001};
    ASSERT_DOUBLE_EQ(nmol.value(), 0.001);
}

TEST_F(SiAmountTest, very_large_amount_values)
{
    si::kilomole kmol{1000000.0};
    ASSERT_DOUBLE_EQ(kmol.value(), 1000000.0);
}

TEST_F(SiAmountTest, add_very_different_scales)
{
    si::millimole mmol{1.0};   // 1 millimole
    si::mole mol{1.0};         // 1 mole = 1000 mmol
    auto result = mmol + mol;
    // Result is in LHS type (millimole)
    // 1 mmol + 1000 mmol = 1001 mmol
    ASSERT_DOUBLE_EQ(result.value(), 1001.0);
}

TEST_F(SiAmountTest, subtract_resulting_in_negative)
{
    si::mole mol1{1.0};
    si::mole mol2{3.0};
    auto result = mol1 - mol2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}


