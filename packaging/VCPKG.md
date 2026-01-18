# vcpkg Package Support

This SI Units library is available via [vcpkg](https://github.com/Microsoft/vcpkg), the Microsoft C++ package manager.

## Installation

### From vcpkg Registry (Community)

Once the library is added to the official vcpkg registry, install with:

```bash
vcpkg install si-units
```

### From Local Port

For development or testing, use the local port:

```bash
vcpkg install si-units --overlay-ports=./vcpkg
```

### From vcpkg.json Manifest

```json
{
  "name": "my-project",
  "version": "1.0.0",
  "dependencies": [
    {
      "name": "si-units",
      "version": "1.0.0"
    }
  ]
}
```

Then run:
```bash
vcpkg install
```

## Usage in CMake

After installation, use in your `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.15)
project(MyProject)

find_package(si-units CONFIG REQUIRED)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE si-units::si-units)
```

## Usage in Code

```cpp
#include <pkr_units/si.h>
#include <pkr_units/si_literals.h>
#include <iostream>

using namespace si::si_literals;

int main() {
    auto distance = 100.0_m;
    auto time = 5.0_s;
    auto velocity = distance / time;
    
    std::cout << "Velocity: " << velocity.value() << " m/s\n";
    return 0;
}
```

## C++ Requirements

- **C++20** or later
- GCC 10+, Clang 10+, MSVC 2019+

## Available Triplets

vcpkg automatically selects the appropriate triplet for your platform:
- `x64-windows`
- `x86-windows`
- `x64-linux`
- `x64-macos`
- And many others...

## Header-Only Benefits

- ✅ No compilation needed during dependency installation
- ✅ Zero runtime overhead
- ✅ Template specialization at compile-time
- ✅ Works with any C++ build system

## Troubleshooting

### "si-units not found"
Ensure you've run `vcpkg integrate install` (for Visual Studio) or properly configured CMake toolchain file.

### Header not found
Make sure to use `find_package(si-units CONFIG REQUIRED)` before linking.

## Documentation

See the main [README](../README.md) and [DESIGN.md](../DESIGN.md) for more information about the library.

## License

Licensed under the MIT License. See LICENSE file for details.
