"""
CMake build handler
"""

from pathlib import Path
from build_utils import run_command, BuildException, print_info


class CMakeBuild:
    """Handles building with CMake"""

    def __init__(self, build_path: Path):
        self.build_path = Path(build_path)

    def build(self, configuration: str) -> None:
        """
        Build the project
        
        Args:
            configuration: Build configuration (Debug or Release)
        """
        cmd = ["cmake", "--build", ".", "--config", configuration]

        try:
            run_command(cmd, cwd=str(self.build_path))
            print_info(f"Build completed successfully!")
            print_info(f"Solution: {self.build_path / 'si_units.sln'}")
        except BuildException as e:
            raise BuildException(f"Build failed: {e}")
