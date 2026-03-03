#include <iostream>
#include <pkr_units/si_units.h>
#include <pkr_units/measurements/measurements.h>
#include <pkr_units/impl/parsing/parse.h>

using namespace pkr::units;
using namespace pkr::units::literals;

int main()
{
    std::cout << "=== Measurement Parsing Examples ===\n\n";

    // ========================================================================
    // Parse linear measurements (linear uncertainty propagation)
    // ========================================================================
    std::cout << "Linear Measurement Parsing:\n";
    std::cout << "----------------------------\n";

    auto linear_result = parse_linear<measurement_lin_t<meter_t<double>>>("5.2 +/- 0.1 m");
    if (linear_result) {
        std::cout << "Parsed linear measurement: ";
        std::cout << linear_result->value() << " +/- " << linear_result->uncertainty() << " m\n";
    } else {
        std::cout << "Failed to parse: " << static_cast<int>(linear_result.error()) << "\n";
    }

    // Wide character version with Unicode separator
    auto linear_wide = parse_linear<measurement_lin_t<kilogram_t<double>>, wchar_t>(L"100.5 ± 0.5 kg");
    if (linear_wide) {
        std::wcout << L"Parsed wide-char linear: " << linear_wide->value() << L" ± " << linear_wide->uncertainty() << L" kg\n";
    }

    std::cout << "\n";

    // ========================================================================
    // Parse RSS measurements (Root Sum of Squares uncertainty)
    // ========================================================================
    std::cout << "RSS Measurement Parsing:\n";
    std::cout << "------------------------\n";

    auto rss_result = parse_rss<measurement_rss_t<second_t<double>>>("42.3 +/- 0.2 s");
    if (rss_result) {
        std::cout << "Parsed RSS measurement: ";
        std::cout << rss_result->value() << " +/- " << rss_result->uncertainty() << " s\n";
    } else {
        std::cout << "Failed to parse: " << static_cast<int>(rss_result.error()) << "\n";
    }

    // Wide character version
    auto rss_wide = parse_rss<measurement_rss_t<meter_t<double>>, wchar_t>(L"12.5 ± 0.3 m");
    if (rss_wide) {
        std::wcout << L"Parsed wide-char RSS: " << rss_wide->value() << L" ± " << rss_wide->uncertainty() << L" m\n";
    }

    std::cout << "\n";

    // ========================================================================
    // Error handling with monadic operations
    // ========================================================================
    std::cout << "Error Handling with Monadic Operations:\n";
    std::cout << "--------------------------------------\n";

    // Using map to transform the result
    auto transformed = parse_linear<measurement_lin_t<meter_t<double>>>("10.0 +/- 0.5 m")
                           .map([](const auto& m) { return m.value() * 2.0; });

    if (transformed) {
        std::cout << "Doubled value after parsing: " << *transformed << " m\n";
    }

    // Using or_else for error recovery
    auto with_default = parse_linear<measurement_lin_t<meter_t<double>>>("invalid +/- 0.1 m")
                            .or_else([](parse_error) { return expected_t<double, parse_error>{0.0}; });

    std::cout << "Value with error recovery: " << *with_default << "\n";

    std::cout << "\n=== Measurement Parsing Complete ===\n";

    return 0;
}
