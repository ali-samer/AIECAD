function(aiecad_build_sandbox)
    aiecad_auto_source(
            OUT_VAR         panels_source_files
            DIRECTORIES     "${TOP_DIR}/sandbox/panels"
            EXTENSIONS      cpp
            TRAVERSE        RECURSE
            FAIL_MODE       FATAL_ERROR
    )

    set(SANDBOX_DIR "${TOP_DIR}/sandbox")

    add_executable(panels ${panels_source_files})
    add_executable(event_bus_practice "${SANDBOX_DIR}/main.cpp")

    target_link_libraries(event_bus_practice PRIVATE aiecad_lib)
    target_link_libraries(panels PRIVATE aiecad_lib)
endfunction()