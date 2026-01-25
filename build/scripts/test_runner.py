"""
Test runner
"""

import subprocess
from build_utils import BuildException, print_success


def run_tests(configuration: str) -> None:
    """
    Run tests using CTest
    
    Args:
        configuration: Build configuration (Debug or Release)
        
    Raises:
        BuildException: If tests fail
    """
    cmd = ["ctest", "-C", configuration, "--output-on-failure", "-V"]

    try:
        # Run without capturing output so test results are visible in console
        result = subprocess.run(cmd, check=False)
        
        if result.returncode != 0:
            raise BuildException(f"Tests failed with exit code {result.returncode}")
        
        print_success("All tests passed!")
        
    except FileNotFoundError:
        raise BuildException("CTest not found. Make sure CMake is properly installed.")
