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
from setup_environment import ensure_environment_ready

# Conda environment name (must match setup scripts)
CONDA_ENV_NAME = "build_si_units_1.0"


def setup_conda_environment(project_root: Path):
    """
    Setup Conda environment if needed.
    Uses setup_environment module to check versions and trigger setup if required.
    """
    print_step("Checking Conda environment")
    ensure_environment_ready(project_root)
    print_success("Conda environment ready!")


def run_in_conda_env_old(cmd, description=None):
    """DEPRECATED: Do not use. Kept for reference."""
    pass


def run_build_in_conda_env(project_root: Path, build_path: Path, config: str, compiler: str, skip_tests: bool, skip_setup: bool):
    """
    Activate Conda environment, run build_impl.py for a specific compiler, ensure deactivation
    Activation and deactivation happen once for the entire build
    Single activation: activate -> run build_impl -> deactivate (in finally block)
    """
    system = platform.system()
    build_impl = build_dir / "scripts" / "build_impl.py"
    
    if system == "Windows":
        # PowerShell script: activate, run build_impl, deactivate in finally
        script_path = build_path / f"_build_session_{compiler}.ps1"
        script_content = f"""
$ErrorActionPreference = "Stop"

# Activate Conda environment
conda activate {CONDA_ENV_NAME}

try {{
    # Run build implementation for specific compiler
    python "{build_impl}" "{project_root}" "{build_path}" `
        --config {config} `
        --compiler {compiler} `
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
            raise Exception(f"Build failed in Conda environment for {compiler}") from e
        finally:
            # Clean up temporary script
            try:
                script_path.unlink()
            except:
                pass
    else:
        # Bash script: activate, run build_impl, deactivate with trap
        script_path = build_path / f"_build_session_{compiler}.sh"
        script_content = f"""#!/bin/bash
set -e

# Activate Conda environment
eval "$(conda shell.bash hook)"
conda activate {CONDA_ENV_NAME}

# Ensure deactivation on exit (success or failure)
trap "conda deactivate" EXIT

# Run build implementation for specific compiler
python "{build_impl}" "{project_root}" "{build_path}" \\
    --config {config} \\
    --compiler {compiler} \\
    {"-no-tests " if skip_tests else ""}{"-skip-setup " if skip_setup else ""}
"""
        script_path.write_text(script_content)
        script_path.chmod(0o755)
        
        try:
            print_step(f"Activating Conda environment: {CONDA_ENV_NAME}")
            cmd = ["bash", str(script_path)]
            subprocess.run(cmd, check=True)
        except subprocess.CalledProcessError as e:
            raise Exception(f"Build failed in Conda environment for {compiler}") from e
        finally:
            # Clean up temporary script
            try:
                script_path.unlink()
            except:
                pass


def main():
    # Clear terminal
    os.system("cls" if platform.system() == "Windows" else "clear")
    
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
        "--compilers",
        default="msvc",
        help="Comma-separated list of compilers to build with (msvc,clang,gcc). Default: msvc",
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
    
    # Parse compiler list
    compilers = [c.strip().lower() for c in args.compilers.split(",")]
    valid_compilers = {"msvc", "clang", "gcc"}
    for compiler in compilers:
        if compiler not in valid_compilers:
            print_error(f"Invalid compiler: {compiler}. Valid options: msvc, clang, gcc")
            sys.exit(1)

    # Setup paths
    project_root = build_dir.parent

    try:
        print_header("SI Units CMake Build Script (Python)")
        print_info(f"Project Root: {project_root}")
        print_info(f"Configuration: {args.config}")
        print_info(f"Compilers: {', '.join(c.upper() for c in compilers)}")
        print_info(f"Conda Environment: {CONDA_ENV_NAME}")
        print_info("")

        # Setup Conda environment (default behavior, can be skipped)
        if not args.skip_venv_setup:
            setup_conda_environment(project_root)
            print_info("")

        # Build for each compiler
        results = {}
        for compiler in compilers:
            compiler_build_path = project_root / f".{compiler}_build"
            
            try:
                print_header(f"\n{'='*60}")
                print_header(f"Building for {compiler.upper()}")
                print_header(f"{'='*60}")
                print_info(f"Build Directory: {compiler_build_path}")
                print_info("")
                
                # Initialize build directory for this compiler
                print_step("Initializing build directory")
                initialize_build_directory(compiler_build_path, clean=args.clean or args.rebuild)
                print()

                # Run build for this compiler
                if not args.skip_venv_setup:
                    print_step("Running build within Conda environment")
                    print_info(f"Activating {CONDA_ENV_NAME}...")
                    run_build_in_conda_env(
                        project_root,
                        compiler_build_path,
                        args.config,
                        compiler,
                        args.no_tests,
                        args.skip_setup
                    )
                    results[compiler] = "[PASSED]"
                else:
                    raise Exception("Conda environment activation is required (use --skip-venv-setup only for testing)")
                    
            except Exception as e:
                print_error(f"Build failed for {compiler.upper()}: {e}")
                results[compiler] = f"[FAILED]: {e}"

        # Print summary
        print_header(f"\n{'='*60}")
        print_header("BUILD SUMMARY")
        print_header(f"{'='*60}")
        for compiler in compilers:
            print_info(f"{compiler.upper():6s}: {results[compiler]}")
        
        # Check if all passed
        all_passed = all("[PASSED]" in result for result in results.values())
        if all_passed:
            print_success("\nAll builds completed successfully!")
        else:
            print_error("\nSome builds failed!")
            sys.exit(1)

    except Exception as e:
        print_error(f"Build failed: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
