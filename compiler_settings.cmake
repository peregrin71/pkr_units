set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Force enable C++ language if not already enabled
if(NOT CMAKE_CXX_COMPILER_LOADED)
    message (ERROR "You forgot to enable C++ language in your CMakeList.txt root file. Add 'enable_language(CXX)' or project(<yourprojectname> LANGUAGES CXX)")
endif()

message (STATUS "===== COMPILER DETECTION DEBUG =====")
message (STATUS "CMAKE_CXX_COMPILER_ID: '${CMAKE_CXX_COMPILER_ID}'")
message (STATUS "CMAKE_CXX_COMPILER: '${CMAKE_CXX_COMPILER}'")
message (STATUS "CMAKE_CXX_COMPILER_LOADED: '${CMAKE_CXX_COMPILER_LOADED}'")
message (STATUS "CMAKE_CXX_COMPILER_WORKS: '${CMAKE_CXX_COMPILER_WORKS}'")
message (STATUS "CXX enabled: '${CMAKE_CXX_COMPILER_LOADED}'")
message (STATUS "CMAKE_CROSSCOMPILING: '${CMAKE_CROSSCOMPILING}'")
message (STATUS "CMAKE_SYSTEM_NAME: '${CMAKE_SYSTEM_NAME}'")
message (STATUS "WIN32 : '${WIN32}'")
message (STATUS "CONAN_CMAKE_SYSROOT: '${CONAN_CMAKE_SYSROOT}'")
message (STATUS "CONAN_CMAKE_FIND_ROOT_PATH: '${CONAN_CMAKE_FIND_ROOT_PATH}'")
message (STATUS "CMAKE_SYSROOT: '${CMAKE_SYSROOT}'")
message (STATUS "CMAKE_FIND_ROOT_PATH: '${CMAKE_FIND_ROOT_PATH}'")

message (STATUS "====================================")

if (NOT CMAKE_CXX_COMPILER_ID )    
    message (FATAL_ERROR "Compiler ID not set - see debug info above")
endif()

message (STATUS "Setting compiler settings for compiler : ${CMAKE_CXX_COMPILER_ID}")

#----------------------------------------------------------------------------------------------------------------------
# Clang

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message (STATUS "[${CMAKE_CURRENT_LIST_FILE})(${CMAKE_CURRENT_LIST_LINE})] : Setting Clang compiler and linker options")
    
    add_compile_options(
        -Wall 
        -Werror 
        -Wno-comment 
        -Wno-unused-command-line-argument
    ) 

    # Only add -fPIC for non-Windows targets
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_compile_options(-fPIC)
    endif()

    #if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    #    add_compile_options( -fsanitize=undefined )
    #endif()

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")

#---------------------------------------------------------------------------------------------------------------------------------------
# MSVC    
# CMB does not always set CMAKE_CXX_COMPILER_ID, so we check for an empty string as well
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") 

add_compile_definitions(VERSION_INFO_FILE="${VERSION_INFO_FILEPATH}")
add_compile_options(
    
    #---------------------------------------------------------------------------------------------------------------------------------------
    # manage warnings
    /W4     #treat warnings as errors
    /WX 
     
    /Wall   # very strict warning level to ensure compatibility with multiple compilers
    /wd4061 # enumerator 'name' in switch of enum 'name' is not explicitly handled by a case label (no problem if there is a default case)
    /wd4068 # unknown pragma
    /wd4296 # 'operator' : expression is always false (this can happen during template/compile time evaluation)
    /wd4355 # 'this' : used in base member initializer list 
    /wd4514 # unreferenced inline function has been removed
    /wd4623 # default constructor was implicitly defined as deleted
    /wd4625 # copy constructor was implicitly defined as deleted
    /wd4626 # assignment operator was implicitly defined as deleted
    /wd4710 # function 'name' not inlined; compiler will not inline function 'name' because it is not defined in the translation unit
    /wd4738 # storing 32-bit float result in memory performance issue
    /wd4711 # function 'name' selected for automatic inline expansion
    /wd4820 # padding added after data member
    /wd4868 # compiler may not enforce left-to-right evaluation order for subexpressions of the && and || operators
    /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    /wd5026 # move constructor was implicitly defined as deleted
    /wd5027 # move assignment operator was implicitly defined as deleted
    /wd5204 # class has virtual functions, but its trivial destructor is not virtual (errors in windows header files)
    #---------------------------------------------------------------------------------------------------------------------------------------
    /wd6378 # 'name' : the compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    /wd6011 # Dereferencing NULL pointer (this can happen in some windows header files)
    /wd28182 # 'name' : the compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    /wd6385 # 'name' : reading invalid data from 'name' (this can happen in some windows header files)
    /wd26495 # Variable 'name' is uninitialized. Always initialize a member variable (this can happen in some windows header files)
    /Z7 
    /MP
    /Ot
    /Oi
    /permissive-            # be more strict about C++ standard compliance
    /utf-8                  # use UTF-8 as the default source file encoding
    /Zc:externConstexpr
    /Zc:throwingNew
    /Zc:inline
    /Zc:rvalueCast
    /Zc:referenceBinding
    /bigobj
    /Zi                     #Produce pdb files
)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
add_compile_definitions(UNICODE _UNICODE)

add_link_options(
    /DEBUG
    /ignore:4099
    /OPT:NOREF
)

else()
    message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")

endif()
 