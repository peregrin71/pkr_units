"""
Conan v1 Package Recipe for SI Units Library

Header-only C++20 SI units library with compile-time dimensional analysis.
Supports Conan v1.x (legacy)
"""

import os
from conans import ConanFile


def _read_version():
    """Read version from version.txt"""
    version_file = os.path.join(os.path.dirname(__file__), "..", "version.txt")
    if os.path.exists(version_file):
        with open(version_file, "r") as f:
            return f.read().strip()
    return "1.0.0"


class SiUnitsConan(ConanFile):
    name = "si_units"
    version = _read_version()
    description = "Header-only C++20 SI units library with compile-time dimensional analysis"
    author = "Thermo Fisher Scientific"
    license = "MIT"
    url = "https://github.com/peregrin71/pkr_si_units"
    homepage = "https://github.com/peregrin71/pkr_si_units"
    
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
    }

    def requirements(self):
        """Test dependencies - optional for consumers"""
        if self.options.get_safe("build_testing"):
            self.requires("gtest/1.8.1")

    def package(self):
        """Package the header-only library"""
        self.copy("*.h", dst="include", src="sdk/include", keep_path=True)
        self.copy("LICENSE*", dst=".", keep_path=False)
        self.copy("README*", dst=".", keep_path=False)

    def package_info(self):
        """Provide package information to consumers"""
        # Header-only library
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        
        # C++20 requirement
        self.cpp_info.cppstd = "20"
