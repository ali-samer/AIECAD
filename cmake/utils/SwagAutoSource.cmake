# ------------------------------------------------------------------------------
# swag_auto_source(
#   OUT_VAR         <result_variable>           # Required
#   DIRECTORIES     <dir1> [<dir2> ...]         # Required: one or more source directories
#
#   [EXTENSIONS      <ext1> [<ext2> ...]]       # Optional: file extensions to include (e.g., cpp, cu, h)
#   [PATTERN         <string|wildcard>]         # Optional: include pattern (e.g., "*_kernel*")
#   [EXCLUDE_PATTERN <string|wildcard>]         # Optional: exclude pattern (e.g., "*_test*")
#
#   [EXCLUDE_DIRECTORIES <dir1> [<dir2> ...]]   # Optional: exclude one or more subdirectories when recursing
#
#   [TRAVERSE RECURSE [DEPTH <n>] | FLAT]       # Optional: RECURSE (default) or FLAT, depth only valid with RECURSE
#   [FOLLOW_SYMLINKS ON|OFF]                    # Optional: default OFF
# )
#
# Description:
#   Collects source files from the given directories, optionally filtered by
#   file extensions and filename patterns. Supports flat or recursive traversal,
#   with optional depth limiting and symlink following.
#
# Example:
#   swag_auto_sources(
#     OUT_VAR         kernal_source_files
#     DIRECTORIES     "${CMAKE_CURRENT_SOURCE_DIR}/src"
#                     "${CMAKE_CURRENT_SOURCE_DIR}/kernels"
#     EXTENSIONS      cpp cu
#     PATTERN         "*_kernel*"
#     EXCLUDE_PATTERN "*_test*"
#     TRAVERSE        RECURSE DEPTH 3
#     FOLLOW_SYMLINKS ON
#   )
# ------------------------------------------------------------------------------

function(swag_auto_source)
    set(options FOLLOW_SYMLINKS)
    set(one_value_args OUT_VAR PATTERN EXCLUDE_PATTERN TRAVERSE DEPTH FAIL_MODE)
    set(multi_value_args DIRECTORIES EXTENSIONS EXCLUDE_DIRECTORIES)

    cmake_parse_arguments(ARG "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})


    if (NOT ARG_OUT_VAR)
        message(FATAL_ERROR "`OUT_VAR` is required. see following syntax: \
                            \nswag_auto_source(\
                                OUT_VAR <my_output_var ...remaining args)")
    endif ()
    if (NOT ARG_DIRECTORIES)
        message(FATAL_ERROR "`DIRECTORIES` is required. see following syntax: \
                            \nswag_auto_source(\
                                DIRECTORIES <dir1> [<dir2>...] ...remaining args)")
    endif ()
    if(NOT DEFINED ARG_TRAVERSE)
        set(ARG_TRAVERSE "RECURSE")
    endif()

    if(ARG_TRAVERSE STREQUAL "RECURSE" AND NOT DEFINED ARG_DEPTH)
        set(ARG_DEPTH "MAX")
    endif()

    if (NOT DEFINED ARG_FAIL_MODE)
        set(ARG_FAIL_MODE "WARNING")
    endif ()

    set(_result_files "")

    foreach(_dir IN LISTS ARG_DIRECTORIES)
        if (NOT IS_DIRECTORY "${_dir}")
            if ("${ARG_FAIL_MODE}" MATCHES "^IGNORE$|^SILENT$")
                continue()
            else ()
                message(${ARG_FAIL_MODE} "The following directory path passed to `DIRECTORIES`\
                                does not exist: ${_dir}")
            endif ()
        endif ()
        if(ARG_TRAVERSE STREQUAL "RECURSE")
            file(GLOB_RECURSE _all_files
                    FOLLOW_SYMLINKS
                    RELATIVE "${_dir}"
                    "${_dir}/*"
            )
        else()
            file(GLOB _all_files
                    FOLLOW_SYMLINKS
                    RELATIVE "${_dir}"
                    "${_dir}/*"
            )
        endif()

        foreach(_file IN LISTS _all_files)
            set(_abs "${_dir}/${_file}")

            set(_skip_dir FALSE)
            foreach(_excl_dir IN LISTS ARG_EXCLUDE_DIRECTORIES)
                string(FIND "${_abs}" "${_excl_dir}" _found)
                if(NOT _found EQUAL -1)
                    set(_skip_dir TRUE)
                endif()
            endforeach()
            if(_skip_dir)
                continue()
            endif()

            if(ARG_TRAVERSE STREQUAL "RECURSE" AND NOT ARG_DEPTH STREQUAL "MAX")
                file(RELATIVE_PATH _rel "${_dir}" "${_abs}")
                string(REPLACE "/" ";" _parts "${_rel}")
                list(LENGTH _parts _depth)
                if(_depth GREATER ARG_DEPTH)
                    continue()
                endif()
            endif()

            get_filename_component(_ext "${_abs}" EXT)
            string(REPLACE "." "" _ext "${_ext}")
            if(ARG_EXTENSIONS AND NOT _ext IN_LIST ARG_EXTENSIONS)
                continue()
            endif()

            if(DEFINED ARG_PATTERN AND NOT _file MATCHES "${ARG_PATTERN}")
                continue()
            endif()

            if(DEFINED ARG_EXCLUDE_PATTERN AND _file MATCHES "${ARG_EXCLUDE_PATTERN}")
                continue()
            endif()

            list(APPEND _result_files "${_abs}")
        endforeach()
    endforeach()

    set(${ARG_OUT_VAR} "${_result_files}" PARENT_SCOPE)
endfunction()