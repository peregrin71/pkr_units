# Clang Compiler Profile (Windows)
# For LLVM Clang on Windows x86_64
# Uses Ninja generator for direct clang compilation
# Includes Undefined Behavior Sanitizer (UBSan) for debug builds

[settings]
os=Windows
arch=x86_64
compiler=clang
compiler.version=18
compiler.libcxx=c++_shared
compiler.cppstd=20
build_type=Debug

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.env.virtualenv:powershell=True

[buildenv]
CC=clang
CXX=clang
CFLAGS=-fsanitize=undefined -fno-sanitize-recover=undefined
CXXFLAGS=-fsanitize=undefined -fno-sanitize-recover=undefined
LDFLAGS=-fsanitize=undefined
