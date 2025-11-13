function(aiecad_build_sandbox)
    aiecad_auto_source(
            OUT_VAR         panels_source_files
            DIRECTORIES     "${TOP_DIR}/sandbox/panels"
            EXTENSIONS      cpp
            TRAVERSE        RECURSE
            FAIL_MODE       FATAL_ERROR
    )

    add_executable(panels
            ${panels_source_files}
    )

    target_link_libraries(panels PRIVATE aiecad_lib)
endfunction()