"""
Build directory initialization
"""

import shutil
from pathlib import Path
from build_utils import print_info


def initialize_build_directory(build_path: Path, clean: bool = False) -> None:
    """
    Initialize the build directory, optionally cleaning it first
    
    Args:
        build_path: Path to build directory
        clean: If True, remove existing build directory
    """
    if clean and build_path.exists():
        print_info(f"Cleaning build directory: {build_path}")
        shutil.rmtree(build_path)

    if not build_path.exists():
        print_info(f"Creating build directory: {build_path}")
        build_path.mkdir(parents=True, exist_ok=True)
