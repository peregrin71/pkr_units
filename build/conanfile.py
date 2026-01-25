"""
Conan Package Recipe for SI Units Library

Header-only C++20 SI units library with compile-time dimensional analysis.

For version-specific implementations, see:
- conanfile_v2.py: Conan v2.0+ (primary/recommended)
- conanfile_v1.py: Conan v1.x (legacy support)

This uses Conan v2 implementation.
"""

import os
from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake, CMakeToolchain, CMakeDeps


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
    requires = "gtest/1.14.0"
    generators = []
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
    }

    def configure(self):
        if self.settings.compiler == "gcc":
            self.settings.compiler.libcxx = "libstdc++11"

    def layout(self):
        # Output generators to the build directory
        # Use compiler-specific build folder if specified, otherwise default to .msvc_build
        # The build folder can be set via CONAN_BUILD_FOLDER environment variable
        import os
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        
        # Check if build folder is specified via environment or use default
        build_folder = os.environ.get('CONAN_BUILD_FOLDER', '.msvc_build')
        generators_path = os.path.join(project_root, build_folder, "generators")
        self.folders.generators = generators_path

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()

    def test(self):
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



