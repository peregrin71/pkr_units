"""
CMake configuration handler
"""

from pathlib import Path
from build_utils import run_command, BuildException


class CMakeConfig:
    """Handles CMake configuration"""

    def __init__(self, project_root: Path, build_path: Path):
        self.project_root = Path(project_root)
        self.build_path = Path(build_path)
        self.toolchain_file = self.build_path / "generators" / "conan_toolchain.cmake"

    def configure(self, configuration: str) -> None:
        """
        Configure the project with CMake
        
        Args:
            configuration: Build configuration (Debug or Release)
        """
        if not self.toolchain_file.exists():
            raise BuildException(
                f"CMake toolchain file not found at: {self.toolchain_file}"
            )

        # CMake configuration arguments
        cmd = [
            "cmake",
            "-G",
            "Visual Studio 17 2022",
            "-DCMAKE_CXX_STANDARD=20",
            f"-DCMAKE_TOOLCHAIN_FILE={self.toolchain_file}",
            str(self.project_root),
        ]

        try:
            run_command(cmd, cwd=str(self.build_path))
        except BuildException as e:
            raise BuildException(f"CMake configuration failed: {e}")
