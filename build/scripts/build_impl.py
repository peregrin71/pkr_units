#!/usr/bin/env python3
"""
SI Units Build Implementation
Runs inside the activated Conda environment
Contains all build logic without environment management
"""

import sys
import os
from pathlib import Path

# Add scripts directory to path for imports
scripts_dir = Path(__file__).parent
sys.path.insert(0, str(scripts_dir))

from build_utils import (
    print_header,
    print_step,
    print_success,
    print_error,
    print_info,
)
from build_environment import initialize_build_environment
from build_directory import initialize_build_directory
from conan_utils import verify_installation, install as conan_install
from cmake_configure import CMakeConfig
from cmake_build import CMakeBuild
from test_runner import run_tests


def run_build(project_root: Path, build_path: Path, config: str, compiler: str, skip_tests: bool, skip_setup: bool):
    """
    Execute the complete build process for a specific compiler
    Assumes Conda environment is already activated
    
    Args:
        project_root: Root of the project
        build_path: Build output directory (specific to compiler)
        config: Build configuration (Debug/Release)
        compiler: Compiler to use (msvc, clang, gcc)
        skip_tests: Skip running tests
        skip_setup: Skip environment setup
    """
    try:
        print_header(f"SI Units Build Implementation - {compiler.upper()} (running in Conda environment)")
        print_info(f"Project Root: {project_root}")
        print_info(f"Build Directory: {build_path}")
        print_info(f"Configuration: {config}")
        print_info(f"Compiler: {compiler.upper()}")
        print_info("")

        # Initialize environment
        if not skip_setup:
            print_step("Initializing build environment")
            initialize_build_environment(scripts_dir)
        else:
            print_info("Skipping dependency setup")
        print()

        # Verify Conan
        print_step("Verifying Conan installation")
        verify_installation()
        print()

        # Initialize build directory
        print_step("Initializing build directory")
        initialize_build_directory(build_path, clean=False)  # Already cleaned in build.py
        print()

        # Change to build directory
        os.chdir(build_path)

        # Install dependencies with compiler-specific profile
        print_step(f"Installing dependencies with Conan ({compiler})")
        conan_install(project_root, build_path, config, compiler)
        print()

        # Configure with CMake
        print_step("Configuring CMake")
        cmake_config = CMakeConfig(project_root, build_path)
        cmake_config.configure(config)
        print()

        # Build
        print_step("Building project")
        cmake_build = CMakeBuild(build_path)
        cmake_build.build(config)
        print()

        # Run tests
        if not skip_tests:
            print_step("Running tests")
            run_tests(config)
            print()

        print_success("Build completed successfully!")
        return 0

    except Exception as e:
        print_error(f"Build failed: {e}")
        return 1


if __name__ == "__main__":
    import argparse
    
    parser = argparse.ArgumentParser(description="Build SI Units project (runs in Conda env)")
    parser.add_argument("project_root", help="Project root directory")
    parser.add_argument("build_path", help="Build output directory")
    parser.add_argument("--config", default="Debug", help="Build configuration")
    parser.add_argument("--compiler", default="msvc", choices=["msvc", "clang", "gcc"], help="Compiler to use")
    parser.add_argument("--no-tests", action="store_true", help="Skip tests")
    parser.add_argument("--skip-setup", action="store_true", help="Skip environment setup")
    
    args = parser.parse_args()
    
    project_root = Path(args.project_root)
    build_path = Path(args.build_path)
    
    sys.exit(run_build(
        project_root,
        build_path,
        args.config,
        args.compiler,
        args.no_tests,
        args.skip_setup
    ))
    
    sys.exit(run_build(project_root, build_path, args.config, args.no_tests, args.skip_setup))
