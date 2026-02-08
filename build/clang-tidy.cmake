#------------------------------------------------------------------------------
# clang-tidy during build
#
# This helper provides a configurable clang-tidy invocation.
# Behavior is conservative by default:
# - Uses a reasonable default check set (can be overridden via CLANG_TIDY_CHECKS)
# - Does NOT apply -fix by default (set env CLANG_TIDY_FIX=1 to enable)
# - Can target an explicit file list via CLANG_TIDY_FILES (space-separated) for incremental checks
# - Optionally treat warnings as errors via CLANG_TIDY_WARNINGS_AS_ERRORS=1
# - Does not add the target to ALL unless CLANG_TIDY_RUN_ALL=1 is set

function(clang_tidy dir)

string(REPLACE "\\" "_" clang_tidy_target ${dir})
string(REPLACE "/" "_" clang_tidy_target ${clang_tidy_target})
string(REPLACE ":" "" clang_tidy_target ${clang_tidy_target})
# Make the target name explicit to avoid collision with other tools (e.g., clang-format)
string(CONCAT clang_tidy_target ${clang_tidy_target} "_clang_tidy")
message (STATUS "[clang-tidy.cmake] clang_tidy_target: ${clang_tidy_target}")

unset(LOCAL_CLANG_TIDY_EXE)
unset(LOCAL_CLANG_TIDY_EXE CACHE)

if(WIN32)
find_program (LOCAL_CLANG_TIDY_EXE
              NAMES clang-tidy bin/clang-tidy
              HINTS CLANG_TIDY_ROOT
                    ENV CLANG_TIDY_ROOT
                    LLVM_ROOT
                    ENV LLVM_ROOT
                    "C:/Program Files/LLVM"
              DOC "Path to clang-tidy executable")
else()
find_program (LOCAL_CLANG_TIDY_EXE
              NAMES clang-tidy bin/clang-tidy
              HINTS CLANG_TIDY_ROOT
                    ENV CLANG_TIDY_ROOT
                    LLVM_ROOT
                    ENV LLVM_ROOT
              DOC "Path to clang-tidy executable")
endif()

if (LOCAL_CLANG_TIDY_EXE)

    # If CLANG_TIDY_FILES is provided (space-separated paths), use that (useful for CI incremental runs)
    if(DEFINED ENV{CLANG_TIDY_FILES} AND NOT "" STREQUAL "$ENV{CLANG_TIDY_FILES}")
        string(REPLACE "\"\"" "" _tmp "$ENV{CLANG_TIDY_FILES}")
        string(REPLACE ";" " " CLANG_TIDY_FILES_LIST "$ENV{CLANG_TIDY_FILES}")
        separate_arguments(CLANG_TIDY_FILES_LIST UNIX_STYLE)
        set(FILTERED_CLANG_TIDY_SOURCE_FILES ${CLANG_TIDY_FILES_LIST})
    else()
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
    endif()

    list(LENGTH FILTERED_CLANG_TIDY_SOURCE_FILES CLANG_TIDY_SOURCE_FILES_COUNT)

    if(CLANG_TIDY_SOURCE_FILES_COUNT GREATER 0)
    message (STATUS "[clang-tidy.cmake] using clang-tidy: ${LOCAL_CLANG_TIDY_EXE}")

    # If the repository provides a top-level .clang-tidy, prefer it and don't pass
    # explicit -checks or -header-filter flags so the file determines behavior.
    if(EXISTS "${CMAKE_SOURCE_DIR}/.clang-tidy")
        message(STATUS "[clang-tidy.cmake] Found repository .clang-tidy, using it for configuration")
        set(USE_CLANG_TIDY_CONFIG_FILE TRUE)
    else()
        if(NOT DEFINED CLANG_TIDY_CHECKS)
            # Conservative, high-signal default set. Expand over time.
            set(CLANG_TIDY_CHECKS "modernize-*,readability-*,bugprone-*,performance-*")
        endif()

        if(NOT DEFINED CLANG_TIDY_HEADER_FILTER)
            set(CLANG_TIDY_HEADER_FILTER ".*pkr_units[\\/].*")
        endif()
    endif()

    # Build flags
    set(_TIDY_CMD ${LOCAL_CLANG_TIDY_EXE})
    list(APPEND _TIDY_CMD -p ${CMAKE_BINARY_DIR})

    # Only pass explicit checks / header-filter when there's no .clang-tidy in the repo.
    if(NOT USE_CLANG_TIDY_CONFIG_FILE)
        list(APPEND _TIDY_CMD -checks=${CLANG_TIDY_CHECKS})
        list(APPEND _TIDY_CMD -header-filter=${CLANG_TIDY_HEADER_FILTER})
    endif()

    if(DEFINED ENV{CLANG_TIDY_WARNINGS_AS_ERRORS} AND "$ENV{CLANG_TIDY_WARNINGS_AS_ERRORS}" STREQUAL "1")
        list(APPEND _TIDY_CMD -warnings-as-errors='*')
    endif()

    if(DEFINED ENV{CLANG_TIDY_FIX} AND "$ENV{CLANG_TIDY_FIX}" STREQUAL "1")
        list(APPEND _TIDY_CMD -fix)
    endif()

    # Determine if the target should be part of the normal build (ALL)
    set(_TARGET_FLAGS)
    if(DEFINED ENV{CLANG_TIDY_RUN_ALL} AND "$ENV{CLANG_TIDY_RUN_ALL}" STREQUAL "1")
        set(_TARGET_FLAGS ALL)
    endif()

    if(NOT TARGET ${clang_tidy_target})
        add_custom_target(${clang_tidy_target} ${_TARGET_FLAGS}
            COMMAND ${_TIDY_CMD}
            ${FILTERED_CLANG_TIDY_SOURCE_FILES}
        )
    else()
        message(STATUS "[clang-tidy.cmake] target ${clang_tidy_target} already exists; skipping add_custom_target to avoid duplicate target")
    endif()
    endif()
    
endif(LOCAL_CLANG_TIDY_EXE)

endfunction(clang_tidy)

#------------------------------------------------------------------------------
