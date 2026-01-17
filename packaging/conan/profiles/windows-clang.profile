# Clang Compiler Profile (Windows)
# For LLVM Clang on Windows x86_64
# Uses Ninja generator for direct clang compilation
# Statically links with libc++ (clang's C++ standard library)
# Note: UBSan requires additional Windows SDK libraries not available in conda env

[settings]
os=Windows
arch=x86_64
compiler=clang
compiler.version=18
compiler.libcxx=c++_static
compiler.cppstd=20
build_type=Debug

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.env.virtualenv:powershell=True

[buildenv]
CC=clang
CXX=clang
