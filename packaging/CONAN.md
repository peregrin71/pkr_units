# Conan Package Support

This SI Units library is available via [Conan](https://conan.io/), a package manager for C and C++.

## Installation

### From ConanCenter (When Published)

Once published to ConanCenter, install with:

```bash
conan install . --requires=si-units/1.0.0
```

### From Local Development

During development, create a local package:

```bash
conan create . --user=dev --channel=testing
```

Then require it:

```bash
conan install . --requires=si-units/1.0.0@dev/testing
```

### Conanfile Requirements

#### For Conan v2.0+ (Recommended)

```python
[requires]
si-units/1.0.0

[generators]
CMakeDeps
CMakeToolchain
```

#### For Conan v1.x (Legacy)

```python
[requires]
si-units/1.0.0

[generators]
cmake
```

## Usage in CMakeLists.txt

### Conan v2.0+

```cmake
cmake_minimum_required(VERSION 3.15)
project(MyProject)

find_package(si-units CONFIG REQUIRED)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE si-units::si-units)
```

### Conan v1.x

```cmake
cmake_minimum_required(VERSION 3.15)
project(MyProject)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(myapp main.cpp)
```

## Usage in Code

```cpp
#include <pkr_units/si.h>
#include <pkr_units/literals.h>
#include <iostream>

using namespace si::literals;

int main() {
    auto mass = 75.0_kg;
    auto acceleration = 9.81_m_per_s2;
    // auto force = mass * acceleration;  // Force calculation example
    
    std::cout << "Mass: " << mass.value() << " kg\n";
    return 0;
}
```

## C++ Requirements

- **C++20** or later
- GCC 10+, Clang 10+, MSVC 2019+

## Conan Versions

### Conan v2.0 (Recommended)

Modern package manager with improved dependency management:

```bash
conan install .
conan build .
conan create .
```

### Conan v1.x (Legacy Support)

Still supported, use:

```bash
conan install .
conan build .
conan create . si-units/1.0.0@user/channel
```

## Development Workflow

### Create a Package from Source

```bash
# Clone the repository
git clone https://github.com/peregrin71/pkr_si_units.git
cd pkr_si_units

# Create local package
conan create . --user=dev --channel=testing

# Use in your project
conan install . --requires=si-units/1.0.0@dev/testing
```

### Using as Local Editable Package

```bash
# From si_units directory
conan editable add . si-units/1.0.0@dev/testing

# In your project
conan install . --requires=si-units/1.0.0@dev/testing

# Changes to si_units are immediately reflected
```

## Header-Only Benefits

- ✅ No compilation needed
- ✅ Zero runtime overhead
- ✅ Fast dependency resolution
- ✅ Works with all C++ build systems

## Troubleshooting

### "Package not found"

Ensure the package is created or available:

```bash
conan search si-units/*
```

### CMake integration issues

Verify CMake version and Conan generators:

```bash
# For Conan v2
cmake --preset=conan-default

# For Conan v1
cmake . -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
```

## Documentation

See the main [README](../README.md) and [DESIGN.md](../DESIGN.md) for more information about the library.

## License

Licensed under the MIT License. See LICENSE file for details.
