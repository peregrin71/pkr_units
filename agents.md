# Copilot and Coding Style Instructions

## Agent behavior
- Be factual and concise. Act like a professional software engineer.
- Do not be complimentary or try to make the user feel good.
- Follow the coding style guidelines outlined in this document.

This file documents the coding style rules for the SI Units library. All code generation and modifications should follow these guidelines.

## Build
- Use `build/build.py` as the primary build entry point for all build-related tasks. Do not invoke PowerShell scripts or CMake commands directly. Refer to `.buildnotes.md` for detailed instructions on usage and options.
- On Windows, use PowerShell syntax in examples and commands.
- On macOS/Linux, use bash syntax in examples and commands.


## C++ Code Style

### Header Guards and Includes
- Use `#pragma once` at the top of header files
- Group includes logically (standard library, project headers)

### Naming Conventions
- **Types/Classes**: `snake_case` (e.g., `meters_per_second_squared`)
- **Variables**: `snake_case` (e.g., `value`, `result`)
- **Functions**: `snake_case` (e.g., `get_value()`)
- **Namespaces**: `snake_case` (e.g., `si`, `si_literals`)
- **Constants**: `UPPER_CASE` (if applicable)

### Function/Method Formatting
- Use `constexpr` where compile-time evaluation is possible
- Use `noexcept` for functions that don't throw
- Use `const` correctness for parameters and member functions
- Parameters: const references for large objects, values for primitives

### Namespace Organization
- Primary namespace: `si`
- Literals namespace: `si::si_literals`
- Implementation details namespace: `si::impl` (if used)

### Comments and Documentation
- Single-line comments above function groups describing their purpose
- No verbose inline comments; code should be self-documenting
- If a file has a copyright header, keep it consistent and at the top

### File Organization
- `#pragma once` (headers only)
- Includes
- Namespace declaration
- Implementations
- Closing namespace comment

### Variable initialization
- Warn if variables are declared without initialization (use default or explicit initialization)
- Use uniform initialization `{}` where applicable
- Use parentheses for aggregate types and direct initialization for primitives
- Call constructors with parentheses for non-aggregate types
