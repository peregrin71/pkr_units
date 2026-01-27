"""
Test runner
"""

import subprocess
from pathlib import Path
from typing import Optional
from build_utils import BuildException, print_success


def _find_test_binary(build_path: Path) -> Path:
    candidates = [
        build_path / "tests" / "si_units_test",
        build_path / "tests" / "si_units_test.exe",
        build_path / "si_units_test",
        build_path / "si_units_test.exe",
    ]
    for candidate in candidates:
        if candidate.exists():
            return candidate
    raise BuildException("si_units_test binary not found in build directory")


def run_tests(configuration: str, env: Optional[dict] = None) -> None:
    """
    Run tests using CTest or directly for coverage
    
    Args:
        configuration: Build configuration (Debug or Release)
        
    Raises:
        BuildException: If tests fail
    """
    if env and "LLVM_PROFILE_FILE" in env:
        # Run test executable directly for coverage
        build_path = Path.cwd()
        test_binary = _find_test_binary(build_path)
        cmd = [str(test_binary)]
        print(f"Running test binary directly: {cmd}")
        print(f"With env LLVM_PROFILE_FILE: {env.get('LLVM_PROFILE_FILE')}")
    else:
        cmd = ["ctest", "-C", configuration, "--output-on-failure", "-V"]

    try:
        # Run without capturing output so test results are visible in console
        result = subprocess.run(cmd, check=False, env=env)
        
        if result.returncode != 0:
            raise BuildException(f"Tests failed with exit code {result.returncode}")
        
        print_success("All tests passed!")
        
    except FileNotFoundError:
        raise BuildException("Test executable or CTest not found. Make sure the build completed successfully.")
