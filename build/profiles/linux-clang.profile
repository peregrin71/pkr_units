[settings]
os=Linux
arch=x86_64
compiler=clang
compiler.version=16
compiler.libcxx=libc++
compiler.cppstd=20

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.build:compiler_executables = {"c": "clang-16", "cpp": "clang++-16"}

[buildenv]
# Add UBSan for debug builds
CXXFLAGS=-fsanitize=undefined -fno-sanitize-recover=undefined
LDFLAGS=-fsanitize=undefined