macro(swag_define_setup_options)
    if (NOT PROJECT_IS_TOP_LEVEL OR IS_MAINTAINER_MODE)
        option(SWAG_BUILD_TESTS "Build swag tests." ON)
        option(SWAG_BUILD_SHARED_LIBS "Build swag as a shared library. Generally discouraged, since swag \
                                         is under active developement and is not guaranteed to result in a stable \
                                         ABI." OFF)
    else ()
        option(SWAG_BUILD_TESTS "Build swag tests." OFF)
        option(SWAG_BUILD_SHARED_LIBS "Build swag as a shared library. Generally discouraged, since swag \
                                         is under active developement and is not guaranteed to result in a stable \
                                         ABI." OFF)
    endif ()

    mark_as_advanced(
            SWAG_BUILD_SHARED_LIBS
    )
endmacro()


macro(swag_set_options)
    swag_define_setup_options()
    set(BUILD_SHARED_LIBS SWAG_BUILD_SHARED_LIBS)
endmacro()