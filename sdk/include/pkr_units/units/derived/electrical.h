#pragma once

#include "../../impl/unit.h"
#include "../../impl/dimension.h"
#include "../../impl/namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Electric charge dimension: A·s
inline constexpr dimension_t electric_charge_dimension{.current = 1, .time = 1};

// Electric potential dimension
inline constexpr dimension_t electric_potential_dimension{2, 1, -3, -1, 0, 0, 0};

// Electric resistance dimension
inline constexpr dimension_t electric_resistance_dimension{2, 1, -3, -2, 0, 0, 0};

// Capacitance dimension
inline constexpr dimension_t capacitance_v{-2, -1, 4, 2, 0, 0, 0};

// Inductance dimension
inline constexpr dimension_t inductance_dimension{2, 1, -2, -2, 0, 0, 0};

// Conductance dimension: S = A²·s³·kg⁻¹·m⁻²
inline constexpr dimension_t conductance_dimension{.length = -2, .mass = -1, .time = 3, .current = 2};

// Electric charge units (Coulomb and derived)
struct coulomb final : public details::unit_t<double, std::ratio<1, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"coulomb"};
    static constexpr std::string_view symbol{"C"};
    static constexpr std::wstring_view w_symbol{L"C"};
    static constexpr std::u8string_view u8_symbol{u8"C"};
};

struct kilocoulomb final : public details::unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilocoulomb"};
    static constexpr std::string_view symbol{"kC"};
    static constexpr std::wstring_view w_symbol{L"kC"};
    static constexpr std::u8string_view u8_symbol{u8"kC"};
};

struct millicoulomb final : public details::unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millicoulomb"};
    static constexpr std::string_view symbol{"mC"};
    static constexpr std::wstring_view w_symbol{L"mC"};
    static constexpr std::u8string_view u8_symbol{u8"mC"};
};

struct microcoulomb final : public details::unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microcoulomb"};
    static constexpr std::string_view symbol{"µC"};
    static constexpr std::wstring_view w_symbol{L"µC"};
    static constexpr std::u8string_view u8_symbol{u8"µC"};
};

struct nanocoulomb final : public details::unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanocoulomb"};
    static constexpr std::string_view symbol{"nC"};
    static constexpr std::wstring_view w_symbol{L"nC"};
    static constexpr std::u8string_view u8_symbol{u8"nC"};
};

struct picocoulomb final : public details::unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picocoulomb"};
    static constexpr std::string_view symbol{"pC"};
    static constexpr std::wstring_view w_symbol{L"pC"};
    static constexpr std::u8string_view u8_symbol{u8"pC"};
};

// Electric potential units (Volt and derived)
struct volt final : public details::unit_t<double, std::ratio<1, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"volt"};
    static constexpr std::string_view symbol{"V"};
    static constexpr std::wstring_view w_symbol{L"V"};
    static constexpr std::u8string_view u8_symbol{u8"V"};
};

struct kilovolt final : public details::unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilovolt"};
    static constexpr std::string_view symbol{"kV"};
    static constexpr std::wstring_view w_symbol{L"kV"};
    static constexpr std::u8string_view u8_symbol{u8"kV"};
};

struct megavolt final : public details::unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megavolt"};
    static constexpr std::string_view symbol{"MV"};
    static constexpr std::wstring_view w_symbol{L"MV"};
    static constexpr std::u8string_view u8_symbol{u8"MV"};
};

struct millivolt final : public details::unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millivolt"};
    static constexpr std::string_view symbol{"mV"};
    static constexpr std::wstring_view w_symbol{L"mV"};
    static constexpr std::u8string_view u8_symbol{u8"mV"};
};

struct microvolt final : public details::unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microvolt"};
    static constexpr std::string_view symbol{"µV"};
    static constexpr std::wstring_view w_symbol{L"µV"};
    static constexpr std::u8string_view u8_symbol{u8"µV"};
};

// Electric resistance units (Ohm and derived)
struct ohm final : public details::unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ohm"};
    static constexpr std::string_view symbol{"Ω"};
    static constexpr std::wstring_view w_symbol{L"Ω"};
    static constexpr std::u8string_view u8_symbol{u8"Ω"};
};

struct kilohm final : public details::unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilohm"};
    static constexpr std::string_view symbol{"kΩ"};
    static constexpr std::wstring_view w_symbol{L"kΩ"};
    static constexpr std::u8string_view u8_symbol{u8"kΩ"};
};

struct megohm final : public details::unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megohm"};
    static constexpr std::string_view symbol{"MΩ"};
    static constexpr std::wstring_view w_symbol{L"MΩ"};
    static constexpr std::u8string_view u8_symbol{u8"MΩ"};
};

struct gigohm final : public details::unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigohm"};
    static constexpr std::string_view symbol{"GΩ"};
    static constexpr std::wstring_view w_symbol{L"GΩ"};
    static constexpr std::u8string_view u8_symbol{u8"GΩ"};
};

struct milliohm final : public details::unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliohm"};
    static constexpr std::string_view symbol{"mΩ"};
    static constexpr std::wstring_view w_symbol{L"mΩ"};
    static constexpr std::u8string_view u8_symbol{u8"mΩ"};
};

struct microohm final : public details::unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microohm"};
    static constexpr std::string_view symbol{"µΩ"};
    static constexpr std::wstring_view w_symbol{L"µΩ"};
    static constexpr std::u8string_view u8_symbol{u8"µΩ"};
};

// Capacitance units (Farad and derived)
struct farad final : public details::unit_t<double, std::ratio<1, 1>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"farad"};
    static constexpr std::string_view symbol{"F"};
    static constexpr std::wstring_view w_symbol{L"F"};
    static constexpr std::u8string_view u8_symbol{u8"F"};
};

struct millifarad final : public details::unit_t<double, std::ratio<1, 1000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"millifarad"};
    static constexpr std::string_view symbol{"mF"};
    static constexpr std::wstring_view w_symbol{L"mF"};
    static constexpr std::u8string_view u8_symbol{u8"mF"};
};

struct microfarad final : public details::unit_t<double, std::ratio<1, 1000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"microfarad"};
    static constexpr std::string_view symbol{"µF"};
    static constexpr std::wstring_view w_symbol{L"µF"};
    static constexpr std::u8string_view u8_symbol{u8"µF"};
};

struct nanofarad final : public details::unit_t<double, std::ratio<1, 1000000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"nanofarad"};
    static constexpr std::string_view symbol{"nF"};
    static constexpr std::wstring_view w_symbol{L"nF"};
    static constexpr std::u8string_view u8_symbol{u8"nF"};
};

struct picofarad final : public details::unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"picofarad"};
    static constexpr std::string_view symbol{"pF"};
    static constexpr std::wstring_view w_symbol{L"pF"};
    static constexpr std::u8string_view u8_symbol{u8"pF"};
};

// Inductance units (Henry and derived)
struct henry final : public details::unit_t<double, std::ratio<1, 1>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, inductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"henry"};
    static constexpr std::string_view symbol{"H"};
    static constexpr std::wstring_view w_symbol{L"H"};
    static constexpr std::u8string_view u8_symbol{u8"H"};
};

struct millihenry final : public details::unit_t<double, std::ratio<1, 1000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, inductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millihenry"};
    static constexpr std::string_view symbol{"mH"};
    static constexpr std::wstring_view w_symbol{L"mH"};
    static constexpr std::u8string_view u8_symbol{u8"mH"};
};

struct microhenry final : public details::unit_t<double, std::ratio<1, 1000000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, inductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microhenry"};
    static constexpr std::string_view symbol{"µH"};
    static constexpr std::wstring_view w_symbol{L"µH"};
    static constexpr std::u8string_view u8_symbol{u8"µH"};
};

struct nanohenry final : public details::unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanohenry"};
    static constexpr std::string_view symbol{"nH"};
    static constexpr std::wstring_view w_symbol{L"nH"};
    static constexpr std::u8string_view u8_symbol{u8"nH"};
};

// Conductance units (Siemens and derived)
struct siemens final : public details::unit_t<double, std::ratio<1, 1>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, conductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"siemens"};
    static constexpr std::string_view symbol{"S"};
    static constexpr std::wstring_view w_symbol{L"S"};
    static constexpr std::u8string_view u8_symbol{u8"S"};
};

struct millisiemens final : public details::unit_t<double, std::ratio<1, 1000>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, conductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millisiemens"};
    static constexpr std::string_view symbol{"mS"};
    static constexpr std::wstring_view w_symbol{L"mS"};
    static constexpr std::u8string_view u8_symbol{u8"mS"};
};

struct microsiemens final : public details::unit_t<double, std::ratio<1, 1000000>, conductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, conductance_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microsiemens"};
    static constexpr std::string_view symbol{"µS"};
    static constexpr std::wstring_view w_symbol{L"µS"};
    static constexpr std::u8string_view u8_symbol{u8"µS"};
};

// ============================================================================
// Most derived unit type specializations for electrical units
// ============================================================================

// Electric charge units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, electric_charge_dimension>
{
    using type = coulomb;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, electric_charge_dimension>
{
    using type = kilocoulomb;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, electric_charge_dimension>
{
    using type = millicoulomb;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using type = microcoulomb;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using type = nanocoulomb;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using type = picocoulomb;
};

// Electric potential units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, electric_potential_dimension>
{
    using type = volt;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, electric_potential_dimension>
{
    using type = kilovolt;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using type = megavolt;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, electric_potential_dimension>
{
    using type = millivolt;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using type = microvolt;
};

// Electric resistance units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, electric_resistance_dimension>
{
    using type = ohm;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, electric_resistance_dimension>
{
    using type = kilohm;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>
{
    using type = megohm;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>
{
    using type = gigohm;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, electric_resistance_dimension>
{
    using type = milliohm;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>
{
    using type = microohm;
};

// Capacitance units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, capacitance_v>
{
    using type = farad;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, capacitance_v>
{
    using type = millifarad;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, capacitance_v>
{
    using type = microfarad;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000>, capacitance_v>
{
    using type = nanofarad;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000000>, capacitance_v>
{
    using type = picofarad;
};

// Inductance units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, inductance_dimension>
{
    using type = henry;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, inductance_dimension>
{
    using type = millihenry;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, inductance_dimension>
{
    using type = microhenry;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000>, inductance_dimension>
{
    using type = nanohenry;
};

// Conductance units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, conductance_dimension>
{
    using type = siemens;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, conductance_dimension>
{
    using type = millisiemens;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, conductance_dimension>
{
    using type = microsiemens;
};

} // PKR_UNITS_NAMESPACE














