# SI Units CMake Build System with Conan2

This project uses Conan2 for dependency management and CMake to build and test the SI Units library with Google Test integration.

## Prerequisites

- Python 3.8+ (for Conan2)
- Conan2 (dependency manager)
- CMake 3.20 or later
- C++20 compatible compiler (MSVC, GCC, or Clang)
- PowerShell 5.0+ (for Windows build scripts)
- Either Ninja or Visual Studio 2022

### Installation on Windows

1. **Install Python**: Download from https://www.python.org/ (add to PATH during installation)

2. **Install Conan2**:
   ```powershell
   pip install conan
   ```

3. **Install CMake**: Download from https://cmake.org/download/

4. **Install Ninja** (recommended):
   ```powershell
   choco install ninja
   ```
   Or download from: https://github.com/ninja-build/ninja/releases

5. **Ensure PowerShell execution policy allows running scripts**:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   ```

6. **Verify Conan installation**:
   ```powershell
   conan --version
   ```

## Building the Project

The build system uses Visual Studio 2022 and MSBuild to generate a solution with projects in the `.vs_build` folder at the project root. **Tests are run automatically by default.**

### Quick Start

From the project root:

**Build and run tests (default behavior):**
```powershell
.\build\build.ps1
```

**First-time build (sets up dependencies, builds, and runs tests):**
```powershell
.\build\build.ps1
```

**Rebuild after making changes:**
```powershell
.\build\build.ps1 -Rebuild
```

**Build with Release configuration:**
```powershell
.\build\build.ps1 -Configuration Release
```

**Build without running tests:**
```powershell
.\build\build.ps1 -NoTests
```

**Fast build (skips dependency checks):**
```powershell
.\build\build.ps1 -SkipSetup
```

### Generated Solution

After the first build, you'll have:
- `.vs_build/si_units.sln` - Main Visual Studio solution
- `.vs_build/` - All project files and build outputs

You can open the solution directly in Visual Studio 2022:
```powershell
Start-Process ".\.vs_build\si_units.sln"
```

### Using PowerShell Scripts

**Build and run tests (just calls main script):**
```powershell
.\build\scripts\test.ps1
```

**Build with Visual Studio (same as main script):**
```powershell
.\build\scripts\build-vs.ps1 -Configuration Debug
```

### Using CMake and Conan Directly

```powershell
# Install dependencies with Conan
conan install . --build=missing

# Configure with CMake
cmake -B .vs_build -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

# Build
cmake --build .vs_build --config Debug

# Run tests
ctest --test-dir .vs_build --output-on-failure
```

## Project Structure

```
si_units/
├── sdk/
│   └── units/
│       ├── si.h
│       └── impl/
│           └── (implementation headers)
├── tests/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── test_si_length.cpp
│   ├── test_si_mass.cpp
│   └── test_si_multi_cast.cpp
├── .vs_build/              ← Generated Visual Studio solution and projects
│   ├── si_units.sln
│   ├── generators/         ← Conan-generated files
│   └── (other build outputs)
├── build/
│   ├── build.ps1           (main build script - Visual Studio)
│   ├── scripts/
│   │   ├── setup-cmake.ps1     (CMake installer/updater)
│   │   ├── setup-conan2.ps1    (Conan2 installer/updater)
│   │   ├── build-vs.ps1        (convenience wrapper)
│   │   └── test.ps1            (build and run tests)
│   └── README.md
├── conanfile.py            (Conan2 dependency configuration)
├── CMakeLists.txt          (root CMake configuration)
└── README.md
```

## CMake Configuration Details

- **C++ Standard**: C++20
- **Build System**: Visual Studio 2022 + MSBuild
- **Dependency Manager**: Conan2
- **Google Test**: Managed by Conan2 (automatically installed)
- **Build Types**: Debug (default) or Release
- **Test Framework**: Google Test with automatic test discovery
- **Build Folder**: `.vs_build` in project root

## Running Tests

Tests are run automatically by default after every build. To skip tests, use:

```powershell
.\build\build.ps1 -NoTests
```

Or run tests manually with CTest:

```powershell
ctest --test-dir .vs_build --output-on-failure
```

## Troubleshooting

### Conan not found
Install Conan2 with: `pip install conan` and ensure it's in your PATH. Restart PowerShell after installation.

### CMake not found
Ensure CMake is installed and in your PATH. Restart PowerShell after installation.

### Ninja not found
Install Ninja with `choco install ninja` or use the Visual Studio generator: `.\build\build-vs.ps1`

### Conan install fails
Check your internet connection. Conan needs to download packages from the Conan Center repository. If behind a proxy, configure Conan settings.

### Google Test not found by CMake
This indicates Conan didn't properly install dependencies. Run:
```powershell
conan install . --build=missing -s build_type=Debug
```

### Compilation errors
Ensure your compiler supports C++20. Update your compiler if necessary.

## Dependency Management

The project uses Conan2 to manage dependencies. To add more dependencies:

1. Edit [conanfile.txt](../conanfile.txt)
2. Add the dependency under `[requires]`:
   ```
   [requires]
   gtest/1.13.0
   zlib/1.2.11
   ```
3. Run `conan install . --build=missing` to download and install

## Project Structure

```
si_units/
├── sdk/
│   └── units/
│       ├── si.h
│       └── impl/
│           └── (implementation headers)
├── tests/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── test_si_length.cpp
│   ├── test_si_mass.cpp
│   └── test_si_multi_cast.cpp
├── build/
│   ├── build.ps1          (main build script)
│   ├── build-vs.ps1       (Visual Studio variant)
│   ├── test.ps1           (build and test)
│   └── README.md
├── conanfile.txt          (Conan2 dependency configuration)
├── CMakeLists.txt         (root CMake configuration)
└── README.md
```
