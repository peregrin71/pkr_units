#----------------------------------------------------------------------------------------------------------------------
# Clang

message (STATUS "[${CMAKE_CURRENT_LIST_FILE})(${CMAKE_CURRENT_LIST_LINE})] : Setting Clang compiler and linker options")

add_compile_options(
    -Wall
    -Wextra
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wnull-dereference
    -Wold-style-cast
    -Woverloaded-virtual
    -Wdouble-promotion
    -Wpedantic
    -Werror
    -Wno-comment
    -Wno-unused-command-line-argument
)

# Coverage (clang + Debug only)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
        add_link_options(-fprofile-instr-generate -fcoverage-mapping)
    else()
        message(WARNING "ENABLE_COVERAGE is only supported for Clang Debug builds")
    endif()
endif()

# Only add -fPIC for non-Windows targets
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_options(-fPIC)
endif()

#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#    add_compile_options( -fsanitize=undefined )
#endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
