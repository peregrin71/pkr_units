"""
Conan package manager utilities
"""

import os
import platform
from pathlib import Path
from build_utils import run_command, BuildException, print_info


def verify_installation() -> None:
    """Verify Conan is installed and accessible"""
    try:
        version = run_command(["conan", "--version"], capture_output=True)
        print_info(f"Conan version: {version}")
    except BuildException:
        raise BuildException(
            "Conan is not installed or not in PATH. "
            "Install from: https://conan.io/"
        )


def install(project_root: Path, build_path: Path, configuration: str, compiler: str = "msvc") -> None:
    """
    Install dependencies using Conan with compiler-specific profile
    
    Args:
        project_root: Root project directory
        build_path: Build output directory (where generators will be written)
        configuration: Build configuration (Debug or Release)
        compiler: Compiler to use (msvc, clang, gcc)
        
    Raises:
        BuildException: If GCC compiler is requested (not supported on Windows)
    """
    # Block GCC on Windows - not supported
    if compiler.lower() == "gcc":
        raise BuildException(
            "ERROR: GCC compilation on Windows is NOT SUPPORTED\n"
            "GCC on Windows uses a cross-compiler configuration that does not work for native development.\n"
            "GCC builds work best on Linux. Use MSVC or Clang on Windows instead."
        )
    
    conanfile = Path(project_root) / "build" / "conanfile.py"
    
    if not conanfile.exists():
        raise BuildException(f"Conanfile not found at: {conanfile}")

    # Use compiler-specific profile
    os_name = platform.system().lower()
    if compiler.lower() == "clang" and os_name == "linux":
        profile_name = "linux-clang.profile"
    else:
        profile_name = f"{os_name}-{compiler}.profile"
    profile_path = Path(project_root) / "build" / "profiles" / profile_name
    if not profile_path.exists():
        raise BuildException(f"Profile not found for compiler '{compiler}': {profile_path}")

    cmd = [
        "conan",
        "install",
        str(conanfile.parent),
        "--build=missing",
        f"-s=build_type={configuration}",
        f"--profile={str(profile_path)}",
        f"--output-folder={str(build_path)}",
    ]

    # Set environment variable for conanfile to know which build folder to use
    env = os.environ.copy()
    build_folder_name = build_path.name  # Get folder name (e.g., ".msvc_build")
    env['CONAN_BUILD_FOLDER'] = build_folder_name

    try:
        run_command(cmd, env=env)
    except BuildException as e:
        raise BuildException(f"Conan install failed: {e}")
