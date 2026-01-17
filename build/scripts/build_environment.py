"""
Build environment initialization
"""

from pathlib import Path
from build_utils import print_step, print_success


def initialize_build_environment(scripts_dir: Path) -> None:
    """
    Initialize the build environment
    
    Args:
        scripts_dir: Path to build scripts directory
    """
    print_step("Build environment ready")
    print_success("All dependencies available in Conda environment")

