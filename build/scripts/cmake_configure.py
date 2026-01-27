"""
CMake configuration handler
"""

from pathlib import Path
from build_utils import run_command, BuildException


class CMakeConfig:
    """Handles CMake configuration"""

    def __init__(self, project_root: Path, build_path: Path, compiler: str = "msvc"):
        self.project_root = Path(project_root)
        self.build_path = Path(build_path)
        self.compiler = compiler.lower()
        self.toolchain_file = self.build_path / "generators" / "conan_toolchain.cmake"

    def _get_generator(self) -> str:
        """Get the appropriate CMake generator for the compiler"""
        if self.compiler == "msvc":
            return "Visual Studio 17 2022"
        elif self.compiler == "clang":
            return "Ninja"
        elif self.compiler == "gcc":
            return "Ninja"
        else:
            raise BuildException(f"Unknown compiler: {self.compiler}")

    def configure(self, configuration: str, enable_coverage: bool = False) -> None:
        """
        Configure the project with CMake
        
        Args:
            configuration: Build configuration (Debug or Release)
        """
        if not self.toolchain_file.exists():
            raise BuildException(
                f"CMake toolchain file not found at: {self.toolchain_file}"
            )

        generator = self._get_generator()

        # CMake configuration arguments
        cmd = [
            "cmake",
            "-G",
            generator,
            "-DCMAKE_CXX_STANDARD=20",
            f"-DCMAKE_TOOLCHAIN_FILE={self.toolchain_file}",
        ]
        if enable_coverage:
            cmd.append("-DENABLE_COVERAGE=ON")

        # For Ninja, we need to specify CMAKE_BUILD_TYPE
        if generator == "Ninja":
            cmd.append(f"-DCMAKE_BUILD_TYPE={configuration}")

        cmd.append(str(self.project_root))

        try:
            run_command(cmd, cwd=str(self.build_path))
        except BuildException as e:
            raise BuildException(f"CMake configuration failed: {e}")
