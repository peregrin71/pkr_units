# MSVC Compiler Profile (Windows)
# For Visual Studio on Windows x86_64

[settings]
os=Windows
arch=x86_64
compiler=msvc
compiler.version=193
compiler.runtime=dynamic
compiler.cppstd=20

[conf]
tools.cmake.cmaketoolchain:generator="Visual Studio 17 2022"

[buildenv]
