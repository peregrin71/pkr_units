# GCC Compiler Profile (Windows)
# For GNU Compiler Collection on Windows x86_64 (MinGW)
# Uses Ninja generator for direct GCC compilation
#
# WARNING: GCC compilation on Windows is NOT SUPPORTED in this environment.
# The conda GCC package is a cross-compiler setup that does not work reliably
# for native Windows development. GCC builds are recommended on Linux instead.
# This profile is kept for reference but will not produce working binaries.

[settings]
os=Windows
arch=x86_64
compiler=gcc
compiler.version=14
compiler.libcxx=libstdc++11
compiler.cppstd=20
build_type=Debug

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.env.virtualenv:powershell=True

[buildenv]
CC=gcc
CXX=g++
