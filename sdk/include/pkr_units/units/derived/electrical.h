#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Electric charge dimension: A·s
inline constexpr dimension_t electric_charge_dimension{0, 0, 1, 1, 0, 0, 0, 0};

// Electric potential dimension
inline constexpr dimension_t electric_potential_dimension{2, 1, -3, -1, 0, 0, 0};

// Electric resistance dimension
inline constexpr dimension_t electric_resistance_dimension{2, 1, -3, -2, 0, 0, 0};

// Capacitance dimension
inline constexpr dimension_t capacitance_v{-2, -1, 4, 2, 0, 0, 0};

// Inductance dimension
inline constexpr dimension_t inductance_dimension{2, 1, -2, -2, 0, 0, 0};

// Conductance dimension: S = A²·s³·kg⁻¹·m⁻²
inline constexpr dimension_t conductance_dimension{-2, -1, 3, 2, 0, 0, 0, 0};

// Electric charge units (Coulomb and derived)
struct coulomb_t final : public details::unit_t<double, std::ratio<1, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"coulomb"};
    static constexpr std::string_view symbol{"C"};
    static constexpr std::wstring_view w_symbol{L"C"};
    static constexpr std::u8string_view u8_symbol{u8"C"};
};

struct kilocoulomb_t final : public details::unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilocoulomb"};
    static constexpr std::string_view symbol{"kC"};
    static constexpr std::wstring_view w_symbol{L"kC"};
    static constexpr std::u8string_view u8_symbol{u8"kC"};
};

struct millicoulomb_t final : public details::unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millicoulomb"};
    static constexpr std::string_view symbol{"mC"};
    static constexpr std::wstring_view w_symbol{L"mC"};
    static constexpr std::u8string_view u8_symbol{u8"mC"};
};

struct microcoulomb_t final : public details::unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microcoulomb"};
    static constexpr std::string_view symbol{"uC"};
    static constexpr std::wstring_view w_symbol{L"µC"};
    static constexpr std::u8string_view u8_symbol{u8"µC"};
};

struct nanocoulomb_t final : public details::unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanocoulomb"};
    static constexpr std::string_view symbol{"nC"};
    static constexpr std::wstring_view w_symbol{L"nC"};
    static constexpr std::u8string_view u8_symbol{u8"nC"};
};

struct picocoulomb_t final : public details::unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picocoulomb"};
    static constexpr std::string_view symbol{"pC"};
    static constexpr std::wstring_view w_symbol{L"pC"};
    static constexpr std::u8string_view u8_symbol{u8"pC"};
};

// Electric potential units (Volt and derived)
struct volt_t final : public details::unit_t<double, std::ratio<1, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"volt"};
    static constexpr std::string_view symbol{"V"};
    static constexpr std::wstring_view w_symbol{L"V"};
    static constexpr std::u8string_view u8_symbol{u8"V"};
};

struct kilovolt_t final : public details::unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilovolt"};
    static constexpr std::string_view symbol{"kV"};
    static constexpr std::wstring_view w_symbol{L"kV"};
    static constexpr std::u8string_view u8_symbol{u8"kV"};
};

struct megavolt_t final : public details::unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megavolt"};
    static constexpr std::string_view symbol{"MV"};
    static constexpr std::wstring_view w_symbol{L"MV"};
    static constexpr std::u8string_view u8_symbol{u8"MV"};
};

struct millivolt_t final : public details::unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millivolt"};
    static constexpr std::string_view symbol{"mV"};
    static constexpr std::wstring_view w_symbol{L"mV"};
    static constexpr std::u8string_view u8_symbol{u8"mV"};
};

struct microvolt_t final : public details::unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microvolt"};
    static constexpr std::string_view symbol{"uV"};
    static constexpr std::wstring_view w_symbol{L"µV"};
    static constexpr std::u8string_view u8_symbol{u8"µV"};
};

// Electric resistance units (Ohm and derived)
struct ohm_t final : public details::unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ohm"};
    static constexpr std::string_view symbol{"ohm"};
    static constexpr std::wstring_view w_symbol{L"Ω"};
    static constexpr std::u8string_view u8_symbol{u8"Ω"};
};

struct kilohm_t final : public details::unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilohm"};
    static constexpr std::string_view symbol{"kohm"};
    static constexpr std::wstring_view w_symbol{L"kΩ"};
    static constexpr std::u8string_view u8_symbol{u8"kΩ"};
};

struct megohm_t final : public details::unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megohm"};
    static constexpr std::string_view symbol{"Mohm"};
    static constexpr std::wstring_view w_symbol{L"MΩ"};
    static constexpr std::u8string_view u8_symbol{u8"MΩ"};
};

struct gigohm_t final : public details::unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigohm"};
    static constexpr std::string_view symbol{"Gohm"};
    static constexpr std::wstring_view w_symbol{L"GΩ"};
    static constexpr std::u8string_view u8_symbol{u8"GΩ"};
};

struct milliohm_t final : public details::unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliohm"};
    static constexpr std::string_view symbol{"mohm"};
    static constexpr std::wstring_view w_symbol{L"mΩ"};
    static constexpr std::u8string_view u8_symbol{u8"mΩ"};
};

struct microohm_t final : public details::unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microohm"};
    static constexpr std::string_view symbol{"uohm"};
    static constexpr std::wstring_view w_symbol{L"µΩ"};
    static constexpr std::u8string_view u8_symbol{u8"µΩ"};
};

// Capacitance units (Farad and derived)
struct farad_t final : public details::unit_t<double, std::ratio<1, 1>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"farad"};
    static constexpr std::string_view symbol{"F"};
    static constexpr std::wstring_view w_symbol{L"F"};
    static constexpr std::u8string_view u8_symbol{u8"F"};
};

struct millifarad_t final : public details::unit_t<double, std::ratio<1, 1000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"millifarad"};
    static constexpr std::string_view symbol{"mF"};
    static constexpr std::wstring_view w_symbol{L"mF"};
    static constexpr std::u8string_view u8_symbol{u8"mF"};
};

struct microfarad_t final : public details::unit_t<double, std::ratio<1, 1000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"microfarad"};
    static constexpr std::string_view symbol{"uF"};
    static constexpr std::wstring_view w_symbol{L"µF"};
    static constexpr std::u8string_view u8_symbol{u8"µF"};
};

struct nanofarad_t final : public details::unit_t<double, std::ratio<1, 1000000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"nanofarad"};
    static constexpr std::string_view symbol{"nF"};
    static constexpr std::wstring_view w_symbol{L"nF"};
    static constexpr std::u8string_view u8_symbol{u8"nF"};
};

struct picofarad_t final : public details::unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"picofarad"};
    static constexpr std::string_view symbol{"pF"};
    static constexpr std::wstring_view w_symbol{L"pF"};
    static constexpr std::u8string_view u8_symbol{u8"pF"};
};

// Inductance units (Henry and derived)
struct henry_t final : public details::unit_t<double, std::ratio<1, 1>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, inductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"henry"};
    static constexpr std::string_view symbol{"H"};
    static constexpr std::wstring_view w_symbol{L"H"};
    static constexpr std::u8string_view u8_symbol{u8"H"};
};

struct millihenry_t final : public details::unit_t<double, std::ratio<1, 1000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, inductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millihenry"};
    static constexpr std::string_view symbol{"mH"};
    static constexpr std::wstring_view w_symbol{L"mH"};
    static constexpr std::u8string_view u8_symbol{u8"mH"};
};

struct microhenry_t final : public details::unit_t<double, std::ratio<1, 1000000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, inductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microhenry"};
    static constexpr std::string_view symbol{"uH"};
    static constexpr std::wstring_view w_symbol{L"µH"};
    static constexpr std::u8string_view u8_symbol{u8"µH"};
};

struct nanohenry_t final : public details::unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanohenry"};
    static constexpr std::string_view symbol{"nH"};
    static constexpr std::wstring_view w_symbol{L"nH"};
    static constexpr std::u8string_view u8_symbol{u8"nH"};
};

// Conductance units (Siemens and derived)
struct siemens_t final : public details::unit_t<double, std::ratio<1, 1>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, conductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"siemens"};
    static constexpr std::string_view symbol{"S"};
    static constexpr std::wstring_view w_symbol{L"S"};
    static constexpr std::u8string_view u8_symbol{u8"S"};
};

struct millisiemens_t final : public details::unit_t<double, std::ratio<1, 1000>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, conductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millisiemens"};
    static constexpr std::string_view symbol{"mS"};
    static constexpr std::wstring_view w_symbol{L"mS"};
    static constexpr std::u8string_view u8_symbol{u8"mS"};
};

struct microsiemens_t final : public details::unit_t<double, std::ratio<1, 1000000>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, conductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microsiemens"};
    static constexpr std::string_view symbol{"uS"};
    static constexpr std::wstring_view w_symbol{L"µS"};
    static constexpr std::u8string_view u8_symbol{u8"µS"};
};

// ============================================================================
// Most derived unit type specializations for electrical units
// ============================================================================

// Electric charge units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, electric_charge_dimension>
{
    using type = coulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, electric_charge_dimension>
{
    using type = kilocoulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, electric_charge_dimension>
{
    using type = millicoulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using type = microcoulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using type = nanocoulomb_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using type = picocoulomb_t;
};

// Electric potential units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, electric_potential_dimension>
{
    using type = volt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, electric_potential_dimension>
{
    using type = kilovolt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using type = megavolt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, electric_potential_dimension>
{
    using type = millivolt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using type = microvolt_t;
};

// Electric resistance units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, electric_resistance_dimension>
{
    using type = ohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, electric_resistance_dimension>
{
    using type = kilohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>
{
    using type = megohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>
{
    using type = gigohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, electric_resistance_dimension>
{
    using type = milliohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>
{
    using type = microohm_t;
};

// Capacitance units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, capacitance_v>
{
    using type = farad_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, capacitance_v>
{
    using type = millifarad_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, capacitance_v>
{
    using type = microfarad_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, capacitance_v>
{
    using type = nanofarad_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000000>, capacitance_v>
{
    using type = picofarad_t;
};

// Inductance units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, inductance_dimension>
{
    using type = henry_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, inductance_dimension>
{
    using type = millihenry_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, inductance_dimension>
{
    using type = microhenry_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, inductance_dimension>
{
    using type = nanohenry_t;
};

// Conductance units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, conductance_dimension>
{
    using type = siemens_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, conductance_dimension>
{
    using type = millisiemens_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, conductance_dimension>
{
    using type = microsiemens_t;
};

} // namespace PKR_UNITS_NAMESPACE
