#------------------------------------------------------------------------------
# clang-tidy during build

function(clang_tidy dir)

string(REPLACE "\\" "_" clang_tidy_target ${dir})
string(REPLACE "/" "_" clang_tidy_target ${clang_tidy_target})
string(REPLACE ":" "" clang_tidy_target ${clang_tidy_target})
message (STATUS "[clang-tidy.cmake] clang_tidy_target: ${clang_tidy_target}")

unset(LOCAL_CLANG_TIDY_EXE)
unset(LOCAL_CLANG_TIDY_EXE CACHE)

if(WIN32)
find_program (LOCAL_CLANG_TIDY_EXE
              NAMES clang-tidy bin/clang-tidy
              HINTS CLANG_TIDY_ROOT}
                    ENV CLANG_TIDY_ROOT
                    LLVM_ROOT
                    ENV LLVM_ROOT
                    "C:/Program Files/LLVM"
              DOC "Path to clang-tidy executable")
else(win32)
find_program (LOCAL_CLANG_TIDY_EXE
              NAMES clang-tidy bin/clang-tidy
              HINTS CLANG_TIDY_ROOT}
                    ENV CLANG_TIDY_ROOT
                    LLVM_ROOT
                    ENV LLVM_ROOT
              DOC "Path to clang-tidy executable")
endif(WIN32)

if (LOCAL_CLANG_TIDY_EXE)

    file(GLOB_RECURSE CLANG_TIDY_SOURCE_FILES 
        "${dir}/*.cc" 
        "${dir}/*.cpp" 
        "${dir}/*.cxx"
        "${dir}/*.c"
    )

    # Exclude files in any "gen" folder
    set(FILTERED_CLANG_TIDY_SOURCE_FILES "")
    foreach(file ${CLANG_TIDY_SOURCE_FILES})
        string(FIND "${file}" "/gen/" gen_folder_pos)
        string(FIND "${file}" "\\gen\\" gen_folder_pos_win)
        if(gen_folder_pos EQUAL -1 AND gen_folder_pos_win EQUAL -1)
            list(APPEND FILTERED_CLANG_TIDY_SOURCE_FILES "${file}")
        endif()
    endforeach()

    list(LENGTH FILTERED_CLANG_TIDY_SOURCE_FILES CLANG_TIDY_SOURCE_FILES_COUNT)

    if(CLANG_TIDY_SOURCE_FILES_COUNT GREATER 0)
    message (STATUS "[clang-tidy.cmake] using clang-tidy: ${LOCAL_CLANG_TIDY_EXE}")

    if(NOT DEFINED CLANG_TIDY_CHECKS)
        set(CLANG_TIDY_CHECKS "modernize-use-braces")
    endif()

    if(NOT DEFINED CLANG_TIDY_HEADER_FILTER)
        set(CLANG_TIDY_HEADER_FILTER ".*pkr_units[\\\\/].*")
    endif()

    add_custom_target(${clang_tidy_target} ALL
        COMMAND ${LOCAL_CLANG_TIDY_EXE}
        -p ${CMAKE_BINARY_DIR}
        -checks=${CLANG_TIDY_CHECKS}
        -header-filter=${CLANG_TIDY_HEADER_FILTER}
        -fix
        -format-style=none
        ${FILTERED_CLANG_TIDY_SOURCE_FILES}
    )
    endif()
    
endif(LOCAL_CLANG_TIDY_EXE)

endfunction(clang_tidy)

#------------------------------------------------------------------------------
