"""
Conan v2 Package Recipe for SI Units Library

Header-only C++20 SI units library with compile-time dimensional analysis.
Supports Conan v2.0+
"""

import os
from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake


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
    generators = "CMakeDeps", "CMakeToolchain"
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
            self.requires("gtest/1.15.0")

    def layout(self):
        cmake_layout(self)

    def build(self):
        """Build tests if requested"""
        if self.options.get_safe("build_testing"):
            cmake = CMake(self)
            cmake.configure()

    def test(self):
        """Run tests if built"""
        if self.options.get_safe("build_testing"):
            cmake = CMake(self)
            cmake.test()

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
        self.cpp_info.cppstdver = "20"
        self.cpp_info.cppstd = "20"
