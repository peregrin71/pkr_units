# Packaging Guide

This directory contains all package manager configurations and documentation for distributing the SI Units library across different package managers.

## Directory Structure

```
packaging/
├── version.txt          # Single source of truth for version (MAJOR.MINOR.PATCH)
├── README.md            # This file
├── CONAN.md             # Conan package manager documentation
├── VCPKG.md             # vcpkg package manager documentation
├── conan/               # Conan package recipes
│   ├── conanfile.py     # Conan v2 wrapper (recommended)
│   ├── conanfile_v2.py  # Conan v2.0+ implementation
│   └── conanfile_v1.py  # Conan v1.x legacy support
└── vcpkg/               # vcpkg package files
    ├── vcpkg.json       # Port configuration
    └── portfile.cmake   # CMake installation script
```

## Version Management

The `version.txt` file is the **single source of truth** for the package version. It contains a semantic version string (e.g., `1.0.0`).

All Conan package recipes (`conanfile.py`, `conanfile_v2.py`, `conanfile_v1.py`) automatically read their version from this file, ensuring consistency across all package manager configurations.

### Updating Version

When releasing a new version:

1. Update `packaging/version.txt` with the new semantic version
2. Commit and tag: `git tag vX.Y.Z`
3. Push to GitHub: `git push origin --tags`
4. Package managers will automatically pick up the version

## Conan Support

The SI Units library supports both modern and legacy Conan installations:

- **Conan v2.0+** (primary): Use `conanfile.py` or `conanfile_v2.py`
- **Conan v1.x** (legacy): Use `conanfile_v1.py`

See [CONAN.md](CONAN.md) for complete installation and usage documentation.

### Key Features

- Header-only C++20 library (no compilation needed)
- Automatic dependency management (GTest for testing)
- CMake integration via `CMakeDeps` and `CMakeToolchain`
- Both Conan v1 and v2 supported

## vcpkg Support

The SI Units library is distributed via vcpkg for convenient package management in Visual Studio projects.

See [VCPKG.md](VCPKG.md) for complete installation and usage documentation.

### Key Features

- Manifest-based installation (`vcpkg.json`)
- Automatic header installation
- C++20 requirement enforcement
- Cross-platform support

## Publishing to Package Registries

### Conan Center

To publish to ConanCenter:

1. Fork [conan-center-index](https://github.com/conan-io/conan-center-index)
2. Create a new recipe directory: `recipes/pkr_units/`
3. Copy `conanfile.py` and update metadata
4. Submit pull request with full test results

### vcpkg Registry

To publish to vcpkg community registry:

1. Fork [vcpkg](https://github.com/Microsoft/vcpkg)
2. Create port directory: `ports/si-units/`
3. Add `portfile.cmake` and `vcpkg.json`
4. Run tests: `./vcpkg install si-units`
5. Submit pull request

## Development Workflow

For local development of the package recipes:

```bash
# Test Conan v2 recipe
conan install packaging/conan/conanfile.py --build=missing

# Test Conan v1 recipe
conan install packaging/conan/conanfile_v1.py --build=missing

# Test vcpkg
vcpkg install si-units --triplet x64-windows
```

## Release Checklist

- [ ] Update `packaging/version.txt`
- [ ] Verify all tests pass: `./build/Invoke-Build.ps1` (Windows) or `./build.sh` (Linux/Mac)
- [ ] Update `CHANGELOG.md` if present
- [ ] Commit changes
- [ ] Create git tag: `git tag vX.Y.Z`
- [ ] Push changes and tags: `git push origin main --tags`
- [ ] Submit to ConanCenter (when ready)
- [ ] Submit to vcpkg registry (when ready)

## Common Issues

**Conan: "conanfile.py not found"**
- Ensure you're running from the project root
- The build script automatically references `packaging/conan/conanfile.py`

**vcpkg: "Cannot find si-units"**
- vcpkg registry submission is required for public availability
- For local testing, use manifest mode with `vcpkg.json` in your project

**Version mismatch across package managers**
- All Conan recipes read from `packaging/version.txt`
- vcpkg.json must be manually updated (future: automate this)

## References

- [Conan Documentation](https://docs.conan.io/)
- [vcpkg Documentation](https://github.com/Microsoft/vcpkg/blob/master/README.md)
- [Semantic Versioning](https://semver.org/)
