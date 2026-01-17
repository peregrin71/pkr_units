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
    cmd = ["ctest", "-C", configuration, "--output-on-failure"]

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, check=False)
        
        if "No tests were found" in result.stdout:
            raise BuildException("No tests found in the test executable!")
        
        if result.returncode != 0:
            raise BuildException(f"Tests failed:\n{result.stdout}\n{result.stderr}")
        
        print_success("All tests passed!")
        
    except FileNotFoundError:
        raise BuildException("CTest not found. Make sure CMake is properly installed.")
