#!/usr/bin/env python3
"""
SI Units CMake Build Script
Orchestrates venv setup, environment activation, and delegates to build_impl.py
"""

import argparse
import sys
import os
import platform
import subprocess
from pathlib import Path

# Add build directory to path for imports
build_dir = Path(__file__).parent
sys.path.insert(0, str(build_dir / "scripts"))

from build_utils import (
    print_header,
    print_step,
    print_success,
    print_error,
    print_info,
)
from build_directory import initialize_build_directory

# Conda environment name (must match setup scripts)
CONDA_ENV_NAME = "build_si_units_1.0"


def setup_conda_environment(project_root: Path):
    """
    Setup Conda environment if needed
    Detects OS and runs appropriate setup script
    """
    system = platform.system()
    
    if system == "Windows":
        setup_script = project_root / "build" / "setup_build_venv.ps1"
        if not setup_script.exists():
            raise Exception(f"Setup script not found: {setup_script}")
        
        print_step("Setting up Conda environment (Windows)")
        cmd = ["powershell", "-ExecutionPolicy", "Bypass", "-File", str(setup_script)]
    else:
        setup_script = project_root / "build" / "setup_build_venv.sh"
        if not setup_script.exists():
            raise Exception(f"Setup script not found: {setup_script}")
        
        print_step("Setting up Conda environment (Unix)")
        cmd = ["bash", str(setup_script)]
    
    try:
        subprocess.run(cmd, check=True)
        print_success("Conda environment setup complete!")
    except subprocess.CalledProcessError:
        raise Exception("Failed to setup Conda environment")


def run_in_conda_env_old(cmd, description=None):
    """DEPRECATED: Do not use. Kept for reference."""
    pass


def run_build_in_conda_env(project_root: Path, build_path: Path, config: str, skip_tests: bool, skip_setup: bool):
    """
    Activate Conda environment, run build_impl.py, ensure deactivation
    Activation and deactivation happen once for the entire build
    Single activation: activate -> run build_impl -> deactivate (in finally block)
    """
    system = platform.system()
    build_impl = build_dir / "scripts" / "build_impl.py"
    
    if system == "Windows":
        # PowerShell script: activate, run build_impl, deactivate in finally
        script_path = build_path / "_build_session.ps1"
        script_content = f"""
$ErrorActionPreference = "Stop"

# Activate Conda environment
conda activate {CONDA_ENV_NAME}

try {{
    # Run build implementation
    python "{build_impl}" "{project_root}" "{build_path}" `
        --config {config} `
        {"-no-tests " if skip_tests else ""}{"-skip-setup " if skip_setup else ""}
    
    if ($LASTEXITCODE -ne 0) {{
        throw "Build implementation failed with exit code $LASTEXITCODE"
    }}
}} finally {{
    # Always deactivate, even on error
    conda deactivate
}}
"""
        script_path.write_text(script_content)
        
        try:
            print_step(f"Activating Conda environment: {CONDA_ENV_NAME}")
            cmd = ["powershell", "-ExecutionPolicy", "Bypass", "-File", str(script_path)]
            subprocess.run(cmd, check=True)
        except subprocess.CalledProcessError as e:
            raise Exception("Build failed in Conda environment") from e
        finally:
            # Clean up temporary script
            try:
                script_path.unlink()
            except:
                pass
    else:
        # Bash script: activate, run build_impl, deactivate with trap
        script_path = build_path / "_build_session.sh"
        script_content = f"""#!/bin/bash
set -e

# Activate Conda environment
eval "$(conda shell.bash hook)"
conda activate {CONDA_ENV_NAME}

# Ensure deactivation on exit (success or failure)
trap "conda deactivate" EXIT

# Run build implementation
python "{build_impl}" "{project_root}" "{build_path}" \\
    --config {config} \\
    {"-no-tests " if skip_tests else ""}{"-skip-setup " if skip_setup else ""}
"""
        script_path.write_text(script_content)
        script_path.chmod(0o755)
        
        try:
            print_step(f"Activating Conda environment: {CONDA_ENV_NAME}")
            cmd = ["bash", str(script_path)]
            subprocess.run(cmd, check=True)
        except subprocess.CalledProcessError as e:
            raise Exception("Build failed in Conda environment") from e
        finally:
            # Clean up temporary script
            try:
                script_path.unlink()
            except:
                pass


def main():
    parser = argparse.ArgumentParser(
        description="Build SI Units project with CMake and Conan"
    )
    parser.add_argument(
        "--config",
        choices=["Debug", "Release"],
        default="Debug",
        help="Build configuration (default: Debug)",
    )
    parser.add_argument(
        "--clean", action="store_true", help="Clean build directory before building"
    )
    parser.add_argument(
        "--rebuild",
        action="store_true",
        help="Clean and rebuild (equivalent to --clean)",
    )
    parser.add_argument(
        "--no-tests",
        action="store_true",
        help="Skip running tests after build",
    )
    parser.add_argument(
        "--skip-setup",
        action="store_true",
        help="Skip dependency setup verification",
    )
    parser.add_argument(
        "--skip-venv-setup",
        action="store_true",
        help="Skip Conda environment setup",
    )

    args = parser.parse_args()

    # Setup paths
    project_root = build_dir.parent
    build_path = project_root / ".vs_build"

    try:
        print_header("SI Units CMake Build Script (Python)")
        print_info(f"Project Root: {project_root}")
        print_info(f"Build Directory: {build_path}")
        print_info(f"Configuration: {args.config}")
        print_info(f"Conda Environment: {CONDA_ENV_NAME}")
        print_info("")

        # Setup Conda environment (default behavior, can be skipped)
        if not args.skip_venv_setup:
            setup_conda_environment(project_root)
            print_info("")

        # Initialize build directory first (before activating env)
        print_step("Initializing build directory")
        initialize_build_directory(build_path, clean=args.clean or args.rebuild)
        print()

        # Run all build steps within a single activated Conda environment session
        if not args.skip_venv_setup:
            print_step("Running build within Conda environment")
            print_info(f"Activating {CONDA_ENV_NAME}...")
            run_build_in_conda_env(project_root, build_path, args.config, args.no_tests, args.skip_setup)
        else:
            raise Exception("Conda environment activation is required (use --skip-venv-setup only for testing)")

        print_success("Build completed successfully!")

    except Exception as e:
        print_error(f"Build failed: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
