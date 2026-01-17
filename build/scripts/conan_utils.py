"""
Conan package manager utilities
"""

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


def install(project_root: Path, configuration: str) -> None:
    """
    Install dependencies using Conan
    
    Args:
        project_root: Root project directory
        configuration: Build configuration (Debug or Release)
    """
    conanfile = Path(project_root) / "packaging" / "conan" / "conanfile.py"
    
    if not conanfile.exists():
        raise BuildException(f"Conanfile not found at: {conanfile}")

    cmd = [
        "conan",
        "install",
        str(conanfile.parent),
        "--build=missing",
        f"-s=build_type={configuration}",
    ]

    try:
        run_command(cmd)
    except BuildException as e:
        raise BuildException(f"Conan install failed: {e}")
