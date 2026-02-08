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


def is_wsl():
    """Check if running on WSL."""
    return "microsoft" in platform.uname().release.lower() or "wsl" in platform.uname().release.lower()


def is_wsl_available():
    """Check if WSL with Ubuntu is available."""
    try:
        result = subprocess.run(["wsl", "--list", "--quiet"], capture_output=True)
        output = result.stdout.decode('utf-16').strip()
        return "Ubuntu" in output
    except:
        return False


def setup_wsl_environment():
    """Setup WSL Ubuntu environment with required tools."""
    print_step("Setting up WSL Ubuntu environment")
    
    # Check if Ubuntu is installed
    try:
        result = subprocess.run(["wsl", "--list", "--quiet"], capture_output=True)
        output = result.stdout.decode('utf-16').strip()
        if "Ubuntu" not in output:
            raise Exception("Ubuntu not installed in WSL. Please install Ubuntu from Microsoft Store.")
    except subprocess.CalledProcessError:
        raise Exception("WSL not available or Ubuntu not installed.")
    
    # Start Ubuntu if not running
    subprocess.run(["wsl", "-d", "Ubuntu", "--", "echo", "Ubuntu started"], check=True)
    
    # Check if clang-18 is installed
    try:
        subprocess.run(["wsl", "-d", "Ubuntu", "--", "which", "clang-18"], check=True)
        print_success("Clang 18 already installed in WSL")
        # Check clang-tidy availability too
        try:
            subprocess.run(["wsl", "-d", "Ubuntu", "--", "which", "clang-tidy-18"], check=True)
            print_success("clang-tidy-18 already installed in WSL")
        except subprocess.CalledProcessError:
            print_info("clang-tidy-18 not found; installing clang-tidy-18 in WSL...")
            try:
                subprocess.run(["wsl", "-u", "root", "-d", "Ubuntu", "--", "bash", "-c", "apt update && apt install -y clang-tidy-18"], check=True)
                print_success("clang-tidy-18 installed in WSL")
            except subprocess.CalledProcessError:
                print_info("Failed to install clang-tidy-18 automatically; please install it manually in WSL if needed")

        # Check clang-format availability too
        try:
            subprocess.run(["wsl", "-d", "Ubuntu", "--", "which", "clang-format-18"], check=True)
            print_success("clang-format-18 already installed in WSL")
        except subprocess.CalledProcessError:
            print_info("clang-format-18 not found; installing clang-format-18 in WSL...")
            try:
                subprocess.run(["wsl", "-u", "root", "-d", "Ubuntu", "--", "bash", "-c", "apt update && apt install -y clang-format-18"], check=True)
                print_success("clang-format-18 installed in WSL")
            except subprocess.CalledProcessError:
                print_info("Failed to install clang-format-18 automatically; please install it manually in WSL if needed")
    except subprocess.CalledProcessError:
        print_info("Clang 18 not found, installing (including clang-tidy)...")
        # Install required packages (include clang-tidy-18)
        install_cmd = """wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null && \\
echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ noble main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null && \\
apt update && apt install -y clang-18 clang-format-18 clang-tidy-18 libc++-18-dev libc++abi-18-dev llvm-18-tools cmake ninja-build python3 python3-venv pipx && \\
pipx ensurepath && \\
pipx install conan || pipx upgrade conan
"""
        
        try:
            subprocess.run(["wsl", "-u", "root", "-d", "Ubuntu", "--", "bash", "-c", install_cmd], check=True)
            print_success("WSL environment setup complete")
            # Verify clang-tidy installed
            try:
                subprocess.run(["wsl", "-d", "Ubuntu", "--", "which", "clang-tidy-18"], check=True)
                print_success("clang-tidy-18 installed in WSL")
            except subprocess.CalledProcessError:
                print_info("clang-tidy-18 still not found after install; you can install it manually in WSL if needed")
        except subprocess.CalledProcessError as e:
            raise Exception(f"Failed to setup WSL environment: {e}")
    
    # Check if conan is installed (try running conan directly in WSL, and include pipx user bin)
    try:
        # Try to run conan --version in a login shell and also check user local pipx bin
        subprocess.run(["wsl", "-d", "Ubuntu", "--", "bash", "-lc", "export PATH=\"$PATH:$HOME/.local/bin\"; conan --version"], check=True)
        print_success("Conan already installed in WSL")
    except subprocess.CalledProcessError:
        print_info("Conan not found, installing...")
        try:
            subprocess.run(
                ["wsl", "-u", "root", "-d", "Ubuntu", "--", "bash", "-c", "apt update && apt install -y python3-venv pipx"],
                check=True,
            )
            subprocess.run(["wsl", "-d", "Ubuntu", "--", "bash", "-c", "pipx ensurepath"], check=True)
            subprocess.run(["wsl", "-d", "Ubuntu", "--", "bash", "-c", "pipx install conan || pipx upgrade conan"], check=True)
            print_success("Conan installed via pipx")
        except subprocess.CalledProcessError as e:
            raise Exception(f"Failed to install Conan: {e}")
    
    # Check CMake version
    try:
        result = subprocess.run(["wsl", "-d", "Ubuntu", "--", "cmake", "--version"], capture_output=True, text=True, check=True)
        version_line = result.stdout.split('\n')[0]
        version = version_line.split()[2]
        major, minor = map(int, version.split('.')[:2])
        if major < 3 or (major == 3 and minor < 20):
            print_info(f"CMake version {version} too old, upgrading...")
            upgrade_cmd = """wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null && \\
echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ noble main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null && \\
apt update && apt install -y cmake
"""
            subprocess.run(["wsl", "-u", "root", "-d", "Ubuntu", "--", "bash", "-c", upgrade_cmd], check=True)
            print_success("CMake upgraded")
        else:
            print_success(f"CMake version {version} is sufficient")
    except subprocess.CalledProcessError:
        print_info("CMake not found, installing...")
        upgrade_cmd = """wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null && \\
echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ noble main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null && \\
apt update && apt install -y cmake
"""
        subprocess.run(["wsl", "-u", "root", "-d", "Ubuntu", "--", "bash", "-c", upgrade_cmd], check=True)
        print_success("CMake installed")
    
    print_success("WSL environment ready")


def run_build_in_wsl(
    project_root: Path,
    build_path: Path,
    config: str,
    compiler: str,
    skip_tests: bool,
    skip_setup: bool,
    enable_coverage: bool,
    clang_tidy_option: str = "off",
    clang_tidy_files: str = "",
    clang_tidy_fix: bool = False,
    clang_tidy_warnings_as_errors: bool = False,
):
    """Run build in WSL Ubuntu environment."""
    build_impl = (build_dir / "scripts" / "build_impl.py").resolve()
    
    # Convert Windows path to WSL path
    def to_wsl_path(win_path):
        drive = win_path.drive.lower()[:-1]  # e.g., 'c'
        path_part = str(win_path)[len(win_path.drive):]
        return f"/mnt/{drive}{path_part}".replace("\\", "/")
    
    wsl_project_root = to_wsl_path(project_root)
    wsl_build_path = to_wsl_path(build_path)
    wsl_build_impl = to_wsl_path(build_impl)
    
    print_info(f"WSL project root: {wsl_project_root}")
    print_info(f"WSL build path: {wsl_build_path}")
    print_info(f"WSL build impl: {wsl_build_impl}")
    
    # Prepare clang-tidy env exports if requested
    tidy_exports = ""
    if clang_tidy_option == "run-all":
        tidy_exports += "export CLANG_TIDY_RUN_ALL=1 && "
    elif clang_tidy_option == "changed-files" and clang_tidy_files:
        # convert semicolons to spaces
        files = clang_tidy_files.replace(';', ' ')
        tidy_exports += f"export CLANG_TIDY_FILES=\"{files}\" && "
    if clang_tidy_fix:
        tidy_exports += "export CLANG_TIDY_FIX=1 && "
    if clang_tidy_warnings_as_errors:
        tidy_exports += "export CLANG_TIDY_WARNINGS_AS_ERRORS=1 && "

    
    # Command to run in WSL
    cmd = f"""
    export PATH="$HOME/.local/bin:$PATH" && \\
    {tidy_exports if tidy_exports else ''}conan profile detect --force && \\
    cd "{wsl_project_root}" && \\
    python3 "{wsl_build_impl}" "{wsl_project_root}" "{wsl_build_path}" \\
        --config {config} \\
        --compiler {compiler} \\
        {"--no-tests " if skip_tests else ""}{"--skip-setup " if skip_setup else ""}{"--coverage " if enable_coverage else ""}
    """
    
    print_info(f"Command: {cmd}")
    
    try:
        print_step("Running build in WSL Ubuntu")
        result = subprocess.run(["wsl", "-d", "Ubuntu", "--", "bash", "-c", cmd], stdout=None, stderr=subprocess.PIPE, text=True, check=True)
        # Output is displayed live in the terminal
    except subprocess.CalledProcessError as e:
        print_error(f"Build failed in WSL: {e.stderr}")
        raise Exception(f"Build failed in WSL for {compiler}") from e


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


def run_build_in_conda_env(project_root: Path, build_path: Path, config: str, compiler: str, skip_tests: bool, skip_setup: bool, enable_coverage: bool, clang_tidy_option: str = "off", clang_tidy_files: str = "", clang_tidy_fix: bool = False, clang_tidy_warnings_as_errors: bool = False):
    """
    Activate Conda environment, run build_impl.py for a specific compiler, ensure deactivation
    Activation and deactivation happen once for the entire build
    Single activation: activate -> run build_impl -> deactivate (in finally block)
    """
    system = platform.system()
    build_impl = (build_dir / "scripts" / "build_impl.py").resolve()
    
    if system == "Windows":
        # PowerShell script: activate, run build_impl, deactivate in finally
        script_path = build_path / f"_build_session_{compiler}.ps1"

        # Prepare optional PowerShell env settings for clang-tidy
        powershell_tidy_env = ""
        if clang_tidy_option == "run-all":
            powershell_tidy_env += "$env:CLANG_TIDY_RUN_ALL = \"1\"\n"
        elif clang_tidy_option == "changed-files" and clang_tidy_files:
            files = clang_tidy_files.replace(';', ' ')
            powershell_tidy_env += f"$env:CLANG_TIDY_FILES = \"{files}\"\n"
        if clang_tidy_fix:
            powershell_tidy_env += "$env:CLANG_TIDY_FIX = \"1\"\n"
        if clang_tidy_warnings_as_errors:
            powershell_tidy_env += "$env:CLANG_TIDY_WARNINGS_AS_ERRORS = \"1\"\n"

        script_content = f"""
$ErrorActionPreference = "Stop"

# Activate Conda environment
conda activate {CONDA_ENV_NAME}

# Ensure clang tools are in PATH
$env:PATH = "$env:CONDA_PREFIX/Library/bin;$env:PATH"

# Optional clang-tidy env
{powershell_tidy_env}

try {{
    # Run build implementation for specific compiler
    python "{build_impl}" "{project_root}" "{build_path}" `
        --config {config} `
        --compiler {compiler} `
        {"--no-tests " if skip_tests else ""}{"--skip-setup " if skip_setup else ""}{"--coverage " if enable_coverage else ""}
    
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

        # Prepare optional bash env settings for clang-tidy
        bash_tidy_env = ""
        if clang_tidy_option == "run-all":
            bash_tidy_env += "export CLANG_TIDY_RUN_ALL=1\n"
        elif clang_tidy_option == "changed-files" and clang_tidy_files:
            files = clang_tidy_files.replace(';', ' ')
            bash_tidy_env += f"export CLANG_TIDY_FILES=\"{files}\"\n"
        if clang_tidy_fix:
            bash_tidy_env += "export CLANG_TIDY_FIX=1\n"
        if clang_tidy_warnings_as_errors:
            bash_tidy_env += "export CLANG_TIDY_WARNINGS_AS_ERRORS=1\n"

        script_content = f"""#!/bin/bash
set -e

# Activate Conda environment
eval "$(conda shell.bash hook)"
conda activate {CONDA_ENV_NAME}

# Ensure deactivation on exit (success or failure)
trap "conda deactivate" EXIT

# Optional clang-tidy env
{bash_tidy_env}

# Run build implementation for specific compiler
python "{build_impl}" "{project_root}" "{build_path}" \\
    --config {config} \\
    --compiler {compiler} \\
    {"--no-tests " if skip_tests else ""}{"--skip-setup " if skip_setup else ""}{"--coverage " if enable_coverage else ""}
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
        "--clang-tidy",
        choices=["off", "run-all", "changed-files"],
        default="off",
        help="Enable clang-tidy integration for local builds: 'run-all' adds the checks to the default build; 'changed-files' expects --clang-tidy-files to be set with a space- or semicolon-separated list of paths",
    )
    parser.add_argument(
        "--clang-tidy-files",
        default="",
        help="Space- or semicolon-separated list of files to pass to clang-tidy when using --clang-tidy=changed-files",
    )
    parser.add_argument(
        "--clang-tidy-fix",
        action="store_true",
        help="If set, will enable automatic -fix during clang-tidy invocation (use with caution)",
    )
    parser.add_argument(
        "--clang-tidy-warnings-as-errors",
        action="store_true",
        help="Treat clang-tidy findings as errors in CI (sets CLANG_TIDY_WARNINGS_AS_ERRORS=1)",
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
    parser.add_argument(
        "--skip-generate-ce-tree",
        action="store_true",
        help="Skip running tools/generate_ce_tree.py after a successful build",
    )
    parser.add_argument(
        "--coverage",
        action="store_true",
        help="Enable coverage reporting (clang Debug on Linux only)",
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
    project_root = build_dir.parent.resolve()
    if not (project_root / "build" / "conanfile.py").exists():
        candidate_root = project_root.parent
        if (candidate_root / "build" / "conanfile.py").exists():
            project_root = candidate_root
            print_info(f"Adjusted project root to: {project_root}")

    try:
        print_header("SI Units CMake Build Script (Python)")
        print_info(f"Project Root: {project_root}")
        print_info(f"Configuration: {args.config}")
        print_info(f"Compilers: {', '.join(c.upper() for c in compilers)}")
        print_info(f"Conda Environment: {CONDA_ENV_NAME}")
        print_info("")

        # Build for each compiler
        results = {}
        for compiler in compilers:
            # Setup environment for this compiler
            if not args.skip_venv_setup:
                if compiler == "clang":
                    setup_wsl_environment()
                else:
                    setup_conda_environment(project_root)
                print_info("")

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
                    if compiler == "clang":
                        print_step("Running build in WSL Ubuntu")
                        run_build_in_wsl(
                            project_root,
                            compiler_build_path,
                            args.config,
                            compiler,
                            args.no_tests,
                            args.skip_setup,
                            args.coverage,
                            clang_tidy_option=args.clang_tidy,
                            clang_tidy_files=args.clang_tidy_files,
                            clang_tidy_fix=args.clang_tidy_fix,
                            clang_tidy_warnings_as_errors=args.clang_tidy_warnings_as_errors,
                        )
                    else:
                        print_step("Running build within Conda environment")
                        print_info(f"Activating {CONDA_ENV_NAME}...")
                        run_build_in_conda_env(
                            project_root,
                            compiler_build_path,
                            args.config,
                            compiler,
                            args.no_tests,
                            args.skip_setup,
                            args.coverage,
                            clang_tidy_option=args.clang_tidy,
                            clang_tidy_files=args.clang_tidy_files,
                            clang_tidy_fix=args.clang_tidy_fix,
                            clang_tidy_warnings_as_errors=args.clang_tidy_warnings_as_errors,
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

            # Generate Compiler Explorer tree for local development
            # Skip this step in CI environments or when explicitly requested
            if not args.skip_generate_ce_tree and not (os.environ.get('CI') or os.environ.get('GITHUB_ACTIONS')):
                script = project_root / 'tools' / 'generate_ce_tree.py'
                if script.exists():
                    try:
                        print_step("Generating Compiler Explorer tree (tools/generate_ce_tree.py)")
                        subprocess.run([sys.executable, str(script)], check=True)
                        print_success("Compiler Explorer tree generated")
                    except subprocess.CalledProcessError as e:
                        # Don't fail the entire build if CE tree generation fails; just print an error
                        print_error(f"Compiler Explorer tree generation failed: {e}")
                else:
                    print_info(f"Skipping Compiler Explorer tree generation (script not found: {script})")
            else:
                print_info("Skipping Compiler Explorer tree generation (CI or skipped by flag)")
        else:
            print_error("\nSome builds failed!")
            sys.exit(1)

    except Exception as e:
        print_error(f"Build failed: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
