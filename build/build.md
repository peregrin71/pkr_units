# Build System Documentation

This directory contains the Python-based build system for SI Units library. The system is designed to be cross-platform, modular, and robust with proper environment lifecycle management.

## Architecture Overview

The build system uses a two-tier architecture to ensure clean separation of concerns and proper environment management:

### Layer 1: Orchestration (build.py)
- **Responsibility**: Manages Conda environment lifecycle (setup, activation, deactivation, error handling)
- **Features**:
  - Detects OS and selects appropriate setup script (PowerShell on Windows, Bash on Unix)
  - Automatically installs Miniconda if not found
  - Creates or updates Miniconda virtual environment with managed tool versions
  - Activates Conda environment once at the start
  - Guarantees deactivation even if build fails
  - Handles all command-line argument parsing and validation

### Layer 2: Implementation (build_impl.py)
- **Responsibility**: Executes all build steps within the activated Conda environment
- **Features**:
  - Runs inside activated Conda environment (no environment management)
  - Orchestrates: Conan dependency installation → CMake configuration → CMake build → Test execution
  - Standalone script that can be executed directly or via build.py
  - Returns appropriate exit codes for error handling

## Quick Start

The build system is fully automated. On first run, it will:
1. Auto-install Miniconda if not present
2. Create a managed Conda environment with all build tools
3. Run the complete build for selected compilers (Conan → CMake → Tests)

### Basic Debug build (MSVC only)
```bash
python build/build.py
```

### Build for multiple compilers
```bash
# Build with MSVC, Clang, and GCC
python build/build.py --compilers msvc,clang,gcc

# Build with MSVC and Clang only
python build/build.py --compilers msvc,clang

# Build with specific compiler
python build/build.py --compilers clang
```

### Release build
```bash
python build/build.py --config Release
```

### Clean rebuild
```bash
python build/build.py --clean
```

### Skip tests
```bash
python build/build.py --no-tests
```

### Skip dependency setup
```bash
python build/build.py --skip-setup
```

### Skip virtual environment setup (if already initialized)
```bash
python build/build.py --skip-venv-setup
```

## Command-Line Options

| Option | Values | Default | Description |
|--------|--------|---------|-------------|
| `--config` | `Debug`, `Release` | `Debug` | CMake build configuration |
| `--compilers` | `msvc,clang,gcc` | `msvc` | Comma-separated list of compilers to build with |
| `--clean` | - | - | Clean build directories before building |
| `--rebuild` | - | - | Alias for `--clean` |
| `--no-tests` | - | - | Skip running tests after build |
| `--skip-setup` | - | - | Skip Conan dependency verification |
| `--skip-venv-setup` | - | - | Skip virtual environment creation (assumes already initialized) |
| `--help` | - | - | Display help message |

## Build Flow

### Single Compiler Build
```
1. Parse arguments
   ↓
2. Set up Conda virtual environment (if not skipped)
   - Windows: Run build/setup_build_venv.ps1 via PowerShell
   - Unix/macOS: Run build/setup_build_venv.sh via Bash
   - Only updates if tool versions have changed
   ↓
3. For each selected compiler:
   a. Initialize compiler-specific build directory (.msvc_build, .clang_build, .gcc_build)
   b. Activate Conda environment (single activation for entire compiler build)
   c. Run build_impl.py inside activated environment:
      - Verify build directory
      - Install Conan dependencies with compiler profile
      - Configure CMake with compiler toolchain
      - Build with appropriate generator (MSVC/Ninja)
      - Run tests (unless --no-tests)
   d. Deactivate Conda environment (guaranteed, even on error)
   ↓
4. Print build summary for all compilers
   ↓
5. Return exit code (0 if all passed, 1 if any failed)
```

### Build Directory Structure
```
.msvc_build/       # MSVC compiler build output
  generators/      # Conan-generated files
  build/          # CMake build output
  tests/          # Compiled test executables
  
.clang_build/      # Clang compiler build output
  generators/
  build/
  tests/
  
.gcc_build/        # GCC compiler build output
  generators/
  build/
  tests/
```

### Compiler Profiles
Each compiler uses a specific Conan profile:
```
build/profiles/windows-msvc.profile   # Visual Studio / MSVC
build/profiles/windows-clang.profile  # LLVM Clang
```

**Note**: Profiles are currently Windows-specific. Future profiles for other platforms:
```
build/profiles/linux-gcc.profile      # GCC on Linux
build/profiles/macos-clang.profile    # Clang on macOS
build/profiles/android-gcc.profile    # GCC for Android (future)
```

Profiles specify:
- OS and architecture
- Compiler identity and version
- C++ standard (C++14)
- Build type (Debug/Release)
- Compiler-specific settings (runtime, libcxx, etc.)

## Module Structure

### Main Entry Points

- **[build.py](build.py)** - Main orchestration script
  - Entry point for all builds
  - Handles Conda environment lifecycle
  - Manages cross-platform wrapper script generation
  - Provides error handling and cleanup

- **[scripts/build_impl.py](scripts/build_impl.py)** - Build implementation
  - Executes all build steps
  - Runs inside activated Conda environment
  - Can be invoked directly for debugging

### Virtual Environment Setup

- **[setup_build_venv.ps1](setup_build_venv.ps1)** - Windows Conda environment setup
  - Creates/updates Miniconda environment on Windows
  - **Auto-installs Miniconda** if not found (to `~/miniconda3`)
  - Installs all required build tools from conda-forge
  - Detects and skips updates if versions unchanged
  - Requires PowerShell 5.0+

- **[setup_build_venv.sh](setup_build_venv.sh)** - Unix/macOS Conda environment setup
  - Creates/updates Miniconda environment on Linux/macOS
  - **Auto-installs Miniconda** if not found (to `~/miniconda3`)
  - Same tool set as Windows version
  - Smart version detection to avoid unnecessary updates

- **[build_venv.yml](build_venv.yml)** - Conda environment specification
  - Auto-generated configuration file
  - Specifies all tool dependencies and versions
  - Uses conda-forge channel only (verified to work without ToS issues)

### Build Utilities (scripts/)

- **build_utils.py** - Common utilities
  - Color-coded console output
  - Command execution with output capture
  - Error handling and reporting

- **build_environment.py** - Environment verification
  - Validates Python environment
  - Checks for required tools
  - Provides diagnostic information

- **build_directory.py** - Build directory management
  - Creates compiler-specific output directories (`.msvc_build/`, `.clang_build/`, `.gcc_build/`)
  - Handles clean rebuild operations
  - Manages CMake intermediate files

- **conan_utils.py** - Conan dependency management
  - Verifies Conan installation
  - Installs project dependencies with compiler-specific profiles
  - Handles different build configurations and compilers

- **cmake_configure.py** - CMake configuration
  - Configures build with appropriate generator
  - Sets up compiler toolchain
  - Configures build options

- **cmake_build.py** - CMake build execution
  - Builds with MSVC, Ninja (for Clang/GCC), or appropriate backend
  - Captures build output
  - Reports build status and errors

- **test_runner.py** - Test execution
  - Locates compiled test executables
  - Runs tests with output capture
  - Reports test results and failures

## Virtual Environment Details

### Conda Environment Name
`build_si_units_1.0`

### Package Channel
`conda-forge` - Provides up-to-date, pre-compiled binaries for all tools

### Installed Tools and Versions

All tools are installed in a managed Miniconda environment and verified to work together:

| Tool | Version | Status | Purpose |
|------|---------|--------|---------|
| Python | 3.12 | ✅ Verified | Runtime (stable through Oct 2028) |
| CMake | 4.2 | ✅ Verified | Build configuration and generation |
| Conan | 2.24 | ✅ Verified | Dependency management (latest stable) |
| LLVM | 21 | ✅ Verified | Compiler toolchain |
| Clang | 21 | ✅ Verified | C++ compiler (LLVM-based) |
| GCC | 13 | ✅ Verified | C++ compiler (GNU) |
| G++ | 13 | ✅ Verified | C++ compiler driver (GNU) |
| Ninja | 1.13 | ✅ Verified | Build backend for CMake |
| clang-tools-extra | 21 | ✅ Available | Includes clang-tidy, clang-format |
| GTest | 1.15.0 | ✅ Verified | Unit testing framework (Conan dependency) |

**Verification Notes:**
- All versions are pinned in setup scripts (build/setup_build_venv.ps1 and setup_build_venv.sh)
- Tools are installed from conda-forge channel (verified to work without ToS issues)
- Build successfully completed on Windows 10/11 with MSVC toolchain
- All unit tests passed in verified environment

### Smart Version Detection

Both setup scripts include intelligent version detection:
- Checks current environment tool versions
- Only updates if versions have changed
- Prevents unnecessary downloads and rebuilds
- Logs version mismatches and updates

## Environment Activation Strategy

### Windows (PowerShell)
- Uses `try`/`finally` block to ensure deactivation
- Wrapper script:
  1. Sources Miniconda environment
  2. Activates `build_si_units_1.0` environment
  3. Executes `python build/scripts/build_impl.py`
  4. Deactivates environment (in finally block)

### Unix/macOS (Bash)
- Uses `trap EXIT` to ensure deactivation on any exit
- Wrapper script:
  1. Sources Miniconda initialization
  2. Activates `build_si_units_1.0` environment
  3. Executes `python build/scripts/build_impl.py`
  4. Trap ensures deactivation even on signal

## Important Design Decisions

### Multi-Compiler Strategy
The build system supports building and testing with multiple compilers in a single invocation:
- Each compiler gets its own isolated build directory
- Each compiler uses a dedicated Conan profile
- Tests run separately for each compiler
- Build summary shows results for all compilers
- Useful for:
  - Code portability validation
  - Compiler-specific warning detection
  - Performance comparison across compilers
  - Pre-commit multi-compiler verification in CI/CD

### Single Activation Lifecycle
The build activates the Conda environment exactly once at the start of each compiler build and deactivates at the end. This approach:
- Avoids repeated activation overhead
- Ensures all build tools use the managed environment consistently
- Simplifies debugging and reproducibility
- Reduces shell startup time

### Guaranteed Cleanup
Both Windows (try/finally) and Unix (trap EXIT) implementations guarantee that the environment is deactivated even if:
- A build step fails
- A signal is received
- An unexpected error occurs
- User cancels the build

### Separation of Concerns
- **build.py**: Zero knowledge of build steps, only manages environment
- **build_impl.py**: Zero knowledge of environment activation, only executes build
- **Setup scripts**: Only create/update tools, never invoke build

This separation enables:
- Easy testing of individual components
- Clear error attribution (environment vs build)
- Simple debugging of environment issues
- Reuse of components in other contexts

## Build Directory Structure

### Workspace Layout
```
si_units/                   # Project root
├── build/                  # Input-only directory (checked in)
│   ├── build.py            # Main orchestration script
│   ├── build_venv.yml      # Conda environment specification
│   ├── scripts/            # Build implementation modules
│   │   ├── build_impl.py
│   │   ├── build_utils.py
│   │   ├── build_environment.py
│   │   ├── build_directory.py
│   │   ├── conan_utils.py
│   │   ├── cmake_configure.py
│   │   ├── cmake_build.py
│   │   └── test_runner.py
│   ├── setup_build_venv.ps1
│   ├── setup_build_venv.sh
│   └── ...
├── .vs_build/              # Output-only directory (generated, not checked in)
│   ├── build/              # CMake build files
│   ├── install/            # Installed binaries/libraries
│   ├── generators/         # Conan generators output
│   └── ...
├── src/                    # Source code
├── tests/                  # Test code
└── ...
```

## Testing Build Scripts

Unit tests are provided for the version matching and parsing logic used in environment setup scripts.

### Running Tests

```bash
cd build/scripts/test
python run_tests.py        # Run all tests (verbose)
python run_tests.py -q     # Quiet output
python -m unittest test_version_utils -v  # Alternative method
```

### Test Coverage

The test suite (`test_version_utils.py`) validates:

- **YmlVersionParser**: Parsing conda yml files for tool versions
  - Simple versions, whitespace handling, hyphenated tool names
  - Comment handling, version operators (=, >=, <=, <, >)
  - Full yml file parsing

- **VersionMatcher**: Comparing configured versions with yml versions
  - Matching and mismatching versions
  - Missing tools detection
  - Internal name mapping (conan2 → conan)
  - LLVM/Clang toolchain multi-part verification
  - Multiple mismatches detection

**Test Results**: 26 tests covering all major scenarios (all passing)

### Version Control

Before modifying `setup_build_venv.ps1` or `setup_build_venv.sh`:

1. Add test cases to `test_version_utils.py`
2. Update `version_utils.py` if needed
3. Run `python run_tests.py` to verify
4. Commit once tests pass

This ensures version matching logic works correctly before deployment.

## Troubleshooting

### Issue: "conda: command not found"
**Status**: ✅ **FIXED** - Miniconda is now auto-installed
- The setup script automatically downloads and installs Miniconda if not found
- No manual installation needed - just run `python build/build.py`

### Issue: "Conda not found in PATH or standard locations"
**Solution**: Miniconda will be automatically installed to `~/miniconda3` on first build run

### Issue: "Python 3.12 not found"
**Solution**: The setup script failed to install Python. Restart the build:
```bash
python build/build.py --clean
```

### Issue: Build fails with "Tool not found"
**Possible Causes**:
1. Conda environment not activated (shouldn't happen - auto-managed now)
2. Tool installation incomplete during venv creation
3. Build interrupted during environment setup

**Solutions**:
- Rebuild environment: `python build/build.py` (re-runs setup)
- Check environment: `conda env list` should show `build_si_units_1.0`
- Verify tools: `conda run -n build_si_units_1.0 cmake --version`

### Issue: CMake configuration fails
**Common Causes**:
1. Compiler not available (MSVC on Windows)
2. Conan dependencies not installed
3. CMake generator mismatch

**Solutions**:
- Clean rebuild: `python build/build.py --clean`
- Check Conan output in build logs
- Verify MSVC/GCC installation in conda environment

### Issue: Tests don't run or fail
**Solutions**:
1. Verify build succeeded: Check `.vs_build/tests/Debug/` or equivalent for test executable
2. Run tests manually: `conda run -n build_si_units_1.0 ctest --test-dir .vs_build --output-on-failure`
3. Clean rebuild if suspicious: `python build/build.py --clean`

### Issue: "Permission denied" on Unix/macOS
**Solution**: Make setup script executable:
```bash
chmod +x build/setup_build_venv.sh
```

### Issue: Conda ToS or channel errors
**Root Cause**: Conda default channels include repositories with Terms of Service requirements
**Solution**: Already handled - setup scripts use conda-forge only channel (verified and tested)

## Configuration Requirements

### Conda Configuration
The build system requires conda-forge as the only package channel (no Anaconda defaults):
```yaml
# ~/.condarc should contain:
channels:
  - conda-forge

channel_priority: strict
```

**Note**: If you have pre-existing conda configuration with other channels (like `defaults`, `pkgs/r`, `pkgs/msys2`), the build will fail with ToS errors. Solution: Remove those channels from your `~/.condarc`.

### Verified Environment
The build has been successfully tested with:
- ✅ Miniconda 25.11.1 (auto-installed)
- ✅ Python 3.12 (in managed conda environment)
- ✅ CMake 4.2 (in managed conda environment)
- ✅ Conan 2.24 (in managed conda environment)
- ✅ LLVM/Clang 21 (in managed conda environment)
- ✅ GCC/G++ 13 (in managed conda environment)
- ✅ Ninja 1.13 (in managed conda environment)
- ✅ Windows 10/11 with Visual Studio 2022 (MSVC)
- ✅ GTest 1.15.0 (Conan dependency)

## Future Enhancements

The infrastructure supports future additions:

### Code Coverage
- LLVM 21 in environment enables llvm-cov-based coverage
- `clang-tools-extra` available (includes llvm-cov)
- Planned: Integration with test_runner.py for coverage reporting

### Static Analysis
- clang-tidy (21) available in environment
- Planned: Pre-build linting step in build_impl.py
- Planned: Configurable warning levels and rule sets

### Code Formatting
- clang-format (21) available in environment  
- Planned: Optional pre-build formatting check
- Planned: Format validation in CI/CD pipeline

### Compiler Profiles
- GCC/G++ 13 available alongside MSVC for cross-compilation testing
- Planned: Profile selection via `--compiler gcc` flag
- Planned: Release build optimizations per compiler

## Related Documentation

- [DESIGN.md](../DESIGN.md) - Project design and architecture
- [TODO.md](../TODO.md) - Outstanding work items
- [CMakeLists.txt](../CMakeLists.txt) - CMake build configuration
- [packaging/](../packaging/) - Package distribution setup
