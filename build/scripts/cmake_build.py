"""
CMake build handler
"""

from pathlib import Path
from build_utils import run_command, BuildException, print_info


class CMakeBuild:
    """Handles building with CMake"""

    def __init__(self, build_path: Path, compiler: str = "msvc"):
        self.build_path = Path(build_path)
        self.compiler = compiler.lower()

    def _is_ninja_build(self) -> bool:
        """Check if this is a Ninja build (for Clang/GCC)"""
        return self.compiler in ["clang", "gcc"]

    def build(self, configuration: str) -> None:
        """
        Build the project
        
        Args:
            configuration: Build configuration (Debug or Release)
        """
        cmd = ["cmake", "--build", "."]

        # For Visual Studio (MSVC), we use --config
        # For Ninja (Clang/GCC), the configuration is already set during CMake configure
        if not self._is_ninja_build():
            cmd.extend(["--config", configuration])

        try:
            run_command(cmd, cwd=str(self.build_path))
            print_info(f"Build completed successfully!")
            if self._is_ninja_build():
                print_info(f"Output directory: {self.build_path}")
            else:
                print_info(f"Solution: {self.build_path / 'si_units.sln'}")
        except BuildException as e:
            raise BuildException(f"Build failed: {e}")
