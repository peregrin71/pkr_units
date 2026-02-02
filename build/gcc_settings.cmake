#----------------------------------------------------------------------------------------------------------------------
# GCC

message (STATUS "[${CMAKE_CURRENT_LIST_FILE})(${CMAKE_CURRENT_LIST_LINE})] : Setting GCC compiler and linker options")

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
)

# Only add -fPIC for non-Windows targets
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_options(-fPIC)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
