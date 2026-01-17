"""
Build environment initialization
"""

from pathlib import Path
from build_utils import print_step, print_success, run_command, BuildException


def initialize_build_environment(scripts_dir: Path) -> None:
    """
    Initialize the build environment by checking dependencies
    
    Args:
        scripts_dir: Path to build scripts directory
    """
    try:
        # Check CMake
        print_step("Checking CMake installation")
        run_command(["cmake", "--version"], capture_output=True)
        print_success("CMake found")

        # Check Conan
        print_step("Checking Conan installation")
        run_command(["conan", "--version"], capture_output=True)
        print_success("Conan found")

    except BuildException as e:
        raise BuildException(
            f"Dependency check failed: {e}\n"
            "Please install CMake and Conan2 before building."
        )
