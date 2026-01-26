# Clang Compiler Profile (Windows)
# For LLVM Clang on Windows x86_64
# Note: Clang on Windows uses MSVC STL, not libc++

[settings]
os=Windows
arch=x86_64
compiler=clang
compiler.version=18
compiler.cppstd=20

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.build:compiler_executables = {"c": "clang", "cpp": "clang++"}

[buildenv]
CC=clang
CXX=clang++