from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake


class SiUnitsConan(ConanFile):
    name = "si_units"
    version = "1.0"
    description = "SI Units library with Google Test support"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("gtest/1.15.0")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        

    def test(self):
        cmake = CMake(self)
        cmake.test()
