macro(aiecad_define_setup_options)
    if (NOT PROJECT_IS_TOP_LEVEL OR IS_MAINTAINER_MODE)
        option(AIECAD_BUILD_TESTS "Build aiecad tests." ON)
        option(AIECAD_BUILD_SHARED_LIBS "Build aiecad as a shared library. Generally discouraged, since aiecad \
                                         is under active developement and is not guaranteed to result in a stable \
                                         ABI." OFF)
    else ()
        option(AIECAD_BUILD_TESTS "Build aiecad tests." OFF)
        option(AIECAD_BUILD_SHARED_LIBS "Build aiecad as a shared library. Generally discouraged, since aiecad \
                                         is under active developement and is not guaranteed to result in a stable \
                                         ABI." OFF)
    endif ()

    mark_as_advanced(
            AIECAD_BUILD_SHARED_LIBS
    )
endmacro()


macro(aiecad_set_options)
    aiecad_define_setup_options()
    set(BUILD_SHARED_LIBS AIECAD_BUILD_SHARED_LIBS)
endmacro()