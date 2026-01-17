#!/usr/bin/env python3
"""
Environment setup and version management for build system.

Uses version_utils.py to check if Conda environment needs updating.
"""

import sys
import os
import platform
import subprocess
from pathlib import Path
from version_utils import YmlVersionParser, VersionMatcher

# Conda environment name (must match setup scripts)
CONDA_ENV_NAME = "build_si_units_1.0"

# Tool versions (must match setup_build_venv.ps1 and setup_build_venv.sh)
TOOL_VERSIONS = {
    "python": "3.12",
    "cmake": "4.2",
    "conan2": "2.24",
    "llvm": "21",
    "clang": "21",
    "gcc": "13",
    "gxx": "13",
    "ninja": "1.13",
}


def check_environment_needs_update(project_root: Path) -> bool:
    """
    Check if Conda environment needs to be updated based on version changes.
    
    Args:
        project_root: Root directory of the project
        
    Returns:
        True if environment needs update, False if versions match
    """
    yml_file = project_root / "build_venv.yml"
    
    if not yml_file.exists():
        # No yml file, needs initial setup
        return True
    
    # Read yml content and parse versions
    yml_content = yml_file.read_text()
    file_versions = YmlVersionParser.parse_yml_content(yml_content)
    
    # Check if versions match
    match, mismatches = VersionMatcher.versions_match(TOOL_VERSIONS, file_versions)
    
    if not match:
        print(f"  Tool versions mismatch:")
        for mismatch in mismatches:
            print(f"    - {mismatch}")
        return True
    
    return False


def setup_conda_environment(project_root: Path):
    """
    Setup Conda environment if needed.
    Detects OS and runs appropriate setup script.
    
    Args:
        project_root: Root directory of the project
    """
    system = platform.system()
    
    if system == "Windows":
        setup_script = project_root / "build" / "setup_build_venv.ps1"
        if not setup_script.exists():
            raise Exception(f"Setup script not found: {setup_script}")
        
        print("  Setting up Conda environment (Windows)...")
        cmd = ["powershell", "-ExecutionPolicy", "Bypass", "-File", str(setup_script)]
    else:
        setup_script = project_root / "build" / "setup_build_venv.sh"
        if not setup_script.exists():
            raise Exception(f"Setup script not found: {setup_script}")
        
        print("  Setting up Conda environment (Unix)...")
        cmd = ["bash", str(setup_script)]
    
    try:
        subprocess.run(cmd, check=True)
    except subprocess.CalledProcessError:
        raise Exception("Failed to setup Conda environment")


def ensure_environment_ready(project_root: Path):
    """
    Ensure Conda environment is ready for building.
    Checks if update is needed and calls setup if required.
    
    Args:
        project_root: Root directory of the project
    """
    if check_environment_needs_update(project_root):
        print("Conda environment needs update")
        setup_conda_environment(project_root)
    else:
        print("Conda environment is up to date")
