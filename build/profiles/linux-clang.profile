[settings]
os=Linux
arch=x86_64
compiler=clang
compiler.version=18
compiler.libcxx=libc++
compiler.cppstd=20

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.build:compiler_executables = {"c": "clang-18", "cpp": "clang++-18"}

[buildenv]
# UBSan removed due to incompatibility with gtest
# CXXFLAGS=-fsanitize=undefined -fno-sanitize-recover=undefined -D_LIBCPP_HAS_FORMAT
# LDFLAGS=-fsanitize=undefined