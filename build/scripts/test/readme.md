# Build Script Tests

Unit tests for build environment setup and version management.

## Running Tests

```bash
cd build/scripts/test
python run_tests.py        # Run all tests (verbose)
python run_tests.py -q     # Quiet output
python -m unittest test_version_utils -v  # Alternative method
```

## Test Coverage

### `test_version_utils.py`

Tests for version parsing and comparison logic used by `setup_build_venv.ps1` and `setup_build_venv.sh`.

**Module tested:** `../version_utils.py`

**Classes tested:**
- `YmlVersionParser` - Parse conda yml files for tool versions
- `VersionMatcher` - Compare configured versions with yml versions
- Convenience functions - High-level version checking

**Test suites:**
- `TestYmlVersionParser` - Parsing of yml content (11 tests)
  - Simple versions, whitespace handling, hyphenated tool names
  - Comment handling, full yml files, edge cases
  
- `TestVersionMatcher` - Version matching logic (14 tests)
  - Matching versions, mismatched versions, missing tools
  - Internal name mapping (conan2 → conan)
  - LLVM/Clang toolchain verification
  - Multiple mismatches, empty versions
  
- `TestConvenienceFunctions` - Wrapper functions (3 tests)
  - parse_yml_dependencies, check_versions
  
- `TestEdgeCases` - Special scenarios (4 tests)
  - Comments, tabs, patch versions, different operators

## Design

The tests use embedded test data (no filesystem access) to verify:

1. **Version Parsing** - Correctly extract tool versions from yml content, handling various formats
2. **Version Comparison** - Detect mismatches between configured and installed versions
3. **Tool Name Mapping** - Handle internal naming (conan2) vs package names (conan)
4. **LLVM/Clang Verification** - Special handling for multi-part toolchain versions

This allows fast, reliable testing without needing actual conda environments.

## Adding New Tests

When updating `setup_build_venv.ps1` or `setup_build_venv.sh`:

1. Add test cases to `test_version_utils.py` for the new logic
2. Update `../version_utils.py` if needed
3. Run tests before committing: `python run_tests.py`

All test data should be embedded as strings in test methods, not loaded from files.

## Module Location

`version_utils.py` is located in the parent directory (`build/scripts/`) so it can be imported and used by other build scripts, not just tests.
