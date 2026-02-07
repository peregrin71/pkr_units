// ============================================================================
// PKR Units - Example Suite Main Entry Point
// ============================================================================
// This program runs all the examples from the documentation to demonstrate
// the key features and patterns of the pkr_units library.
//
// Each example is in its own .cpp file and demonstrates a specific feature:
//  1. First Example      - Basic units and velocity calculation
//  2. Kinetic Energy     - Physics formula with type deduction and literals
//  3. Unit Conversion    - Cross-system conversion (SI ↔ Imperial)
//  4. Literals           - User-defined literals with multiple unit scales
//  5. Type Safety        - Compiler-enforced dimensional correctness
//  6. Physics Funcs      - Type-safe physics equations
//  7. Derived Units      - Automatic type deduction from operations
//  8. Temperature        - Affine vs linear quantities
//  9. Electrical Eng     - AC/DC circuits, power, and three-phase systems
//

#include <iostream>
#include <string>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

namespace ex {
    // Example 1: First Example
    void example_first_example();
    
    // Example 2: Kinetic Energy
    void example_kinetic_energy();
    
    // Example 3: Unit Conversion
    void example_unit_conversion();
    
    // Example 4: Literals
    void example_literals();
    
    // Example 5: Type Safety
    void example_type_safety();
    
    // Example 6: Physics Functions
    void example_physics_functions();
    
    // Example 7: Derived Units
    void example_derived_units();
    
    // Example 8: Temperature
    void example_temperature();
    
    // Example 9: Electrical Engineering
    void example_electrical_engineering();
}

int main()
{
    // Enable UTF-8 output on Windows console for wide character streams
    #ifdef _WIN32
        _setmode(_fileno(stdout), _O_U8TEXT);
    #endif
    
    std::wcout << L"================================================================================\n";
    std::wcout << L"PKR Units - Comprehensive Examples\n";
    std::wcout << L"================================================================================\n";
    std::wcout << L"This suite demonstrates key features of the dimensional analysis library.\n";
    std::wcout << L"Each section shows practical patterns for type-safe unit calculations and\n";
    std::wcout << L"physics/engineering domain applications.\n";
    
    try {
        // Run all examples
        ex::example_first_example();
        std::wcout.flush();
        std::wcout << L"[Example 1 completed]\n";
        
        ex::example_kinetic_energy();
        std::wcout.flush();
        std::wcout << L"[Example 2 completed]\n";
        
        ex::example_unit_conversion();
        std::wcout.flush();
        std::wcout << L"[Example 3 completed]\n";
        
        ex::example_literals();
        std::wcout.flush();
        std::wcout << L"[Example 4 completed]\n";
        
        ex::example_type_safety();
        std::wcout.flush();
        std::wcout << L"[Example 5 completed]\n";
        
        ex::example_physics_functions();
        std::wcout.flush();
        std::wcout << L"[Example 6 completed]\n";
        
        ex::example_derived_units();
        std::wcout.flush();
        std::wcout << L"[Example 7 completed]\n";
        
        ex::example_temperature();
        std::wcout.flush();
        std::wcout << L"[Example 8 completed]\n";
        
        ex::example_electrical_engineering();
        std::wcout.flush();
        std::wcout << L"[Example 9 completed]\n";
        
        std::wcout << L"\n================================================================================\n";
        std::wcout << L"All examples completed successfully!\n";
        std::wcout << L"================================================================================\n";
        
        return 0;
    }
    catch (const std::exception& e) {
        // Convert narrow exception message to display in wcerr
        std::string error_msg = e.what();
        std::wstring werror_msg;
        for (char c : error_msg) {
            werror_msg += static_cast<wchar_t>(static_cast<unsigned char>(c));
        }
        std::wcerr << L"Standard exception: " << werror_msg << std::endl;
        return 1;
    }
    catch (...) {
        std::wcerr << L"Unknown exception occurred!\n";
        return 1;
    }
}