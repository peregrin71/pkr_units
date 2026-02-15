#------------------------------------------------------------------------------
# clang-format during build

function(clang_format dir)

string(REPLACE "\\" "_" clang_format_target ${dir})
string(REPLACE "/" "_" clang_format_target ${clang_format_target})
string(REPLACE ":" "" clang_format_target ${clang_format_target})
message (STATUS "[clang-format.cmake] clang_format_target: ${clang_format_target}")

unset(LOCAL_CLANG_FORMAT_EXE)
unset(LOCAL_CLANG_FORMAT_EXE CACHE)

if(WIN32)
find_program (LOCAL_CLANG_FORMAT_EXE
              NAMES clang-format bin/clang-format
              HINTS CLANG_FORMAT_ROOT
                    ENV CLANG_FORMAT_ROOT
                    LLVM_ROOT
                    ENV LLVM_ROOT
                    "C:/Program Files/LLVM"
              DOC "Path to clang-format executable")
else(win32)
find_program (LOCAL_CLANG_FORMAT_EXE
              NAMES clang-format bin/clang-format
              HINTS CLANG_FORMAT_ROOT
                    ENV CLANG_FORMAT_ROOT
                    LLVM_ROOT
                    ENV LLVM_ROOT
              DOC "Path to clang-format executable")
endif(WIN32)              

if (LOCAL_CLANG_FORMAT_EXE)

    file(GLOB_RECURSE CLANG_FORMAT_FILES 
        "${dir}/*.cc" 
        "${dir}/*.cpp" 
        "${dir}/*.cxx"
        "${dir}/*.h"
        "${dir}/*.hh"
        "${dir}/*.hpp"
        "${dir}/*.hxx"
        "${dir}/*.inl"
    )

    # Exclude files in any "gen" folder
    set(FILTERED_CLANG_FORMAT_FILES "")
    foreach(file ${CLANG_FORMAT_FILES})
        string(FIND "${file}" "/gen/" gen_folder_pos)
        string(FIND "${file}" "\\gen\\" gen_folder_pos_win)
        if(gen_folder_pos EQUAL -1 AND gen_folder_pos_win EQUAL -1)
            list(APPEND FILTERED_CLANG_FORMAT_FILES "${file}")
        endif()
    endforeach()

    list(LENGTH FILTERED_CLANG_FORMAT_FILES CLANG_FORMAT_FILES_COUNT)

    if(CLANG_FORMAT_FILES_COUNT GREATER 0)
    message (STATUS "[clang-format.cmake] using clang-format: ${LOCAL_CLANG_FORMAT_EXE}")

    add_custom_target(${clang_format_target} ALL
        COMMAND ${LOCAL_CLANG_FORMAT_EXE}
        -i ${FILTERED_CLANG_FORMAT_FILES}
    )
    endif()
    
endif(LOCAL_CLANG_FORMAT_EXE)

endfunction(clang_format)

#------------------------------------------------------------------------------
