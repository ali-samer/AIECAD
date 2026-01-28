cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "Setting C++ standard to c++${CMAKE_CXX_STANDARD}")

set(CMAKE_MODULE_PATH
        "${CMAKE_MODULE_PATH}"
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}"
        "${CMAKE_BINARY_DIR}/Release/generators"
        "${CMAKE_BINARY_DIR}/Release"
)

project(aiecad
        VERSION 0.1.0
        DESCRIPTION "Spatial Wiring for AIE Grid"
        LANGUAGES CXX C
)

# TODO: installation rules to be determined
set(INCLUDE_INSTALL_DIR include CACHE STRING
        "The subdirectory where header files should be installed"
)
set(LIB_INSTALL_DIR lib CACHE STRING
        "The subdirectory where library files should be installed"
)
set(BIN_INSTALL_DIR bin CACHE STRING
        "The subdirectory where binary files should be installed"
)
set(CMAKE_INSTALL_DIR lib/cmake/aiecad CACHE STRING
        "The subdirectory where CMake configuration files should be installed"
)

include(settings/ProjectOptions)
aiecad_set_options()

set(TOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(AIECAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/aiecad")
string(REGEX REPLACE "(.)" [[\\\1]] AIECAD_DIR_REGEX_ESCAPED "${AIECAD_DIR}")

include(checks/AIECADPlatformChecks)
include(utils/AIECADAutoSource)

aiecad_auto_source(
        OUT_VAR             src_files
        DIRECTORIES         "${AIECAD_DIR}"
        EXCLUDE_DIRECTORIES
            "${AIECAD_DIR}/test"
            "${AIECAD_DIR}/memory"
            "${AIECAD_DIR}/aiecad-compiler"
        EXTENSIONS          cpp
        TRAVERSE            RECURSE
        FAIL_MODE           FATAL_ERROR
)

aiecad_auto_source(
        OUT_VAR             header_files
        DIRECTORIES         "${AIECAD_DIR}"
        EXCLUDE_DIRECTORIES
            "${AIECAD_DIR}/test"
            "${AIECAD_DIR}/memory"
            "${AIECAD_DIR}/aiecad-compiler"
        EXTENSIONS          h hpp
        TRAVERSE            RECURSE
        FAIL_MODE           FATAL_ERROR
)

include(ProjectDeps)
include(checks/AIECADConfigs)

add_library(aiecad_deps INTERFACE)

if (AIECAD_INCLUDE_DIRS)
    target_include_directories(aiecad_deps INTERFACE ${AIECAD_INCLUDE_DIRS})
endif()
if (AIECAD_LINK_LIBS)
    target_link_libraries(aiecad_deps INTERFACE ${AIECAD_LINK_LIBS})
endif()
if (AIECAD_COMPILE_OPTS)
    target_compile_options(aiecad_deps INTERFACE ${AIECAD_COMPILE_OPTS})
endif()
if (AIECAD_COMPILE_DEFS)
    message(STATUS "adding compile defs...")
    target_compile_definitions(aiecad_deps INTERFACE ${AIECAD_COMPILE_DEFS} )
else ()
    message(STATUS "no compile defs...")
endif()

if (XRT_LIBDIR)
    set_target_properties(aiecad_deps PROPERTIES
            BUILD_WITH_INSTALL_RPATH TRUE
            BUILD_RPATH   "${XRT_LIBDIR}"
            INSTALL_RPATH "$ORIGIN;${XRT_LIBDIR}"
    )
endif()

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/aiecad)
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/aiecad-config.h.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/aiecad/aiecad-config.h"
)

set(AIECAD_IMGUI_BINDINGS_DIR "" CACHE PATH "Path to Dear ImGui backends/ folder (leave empty to auto-detect)")

if (NOT AIECAD_IMGUI_BINDINGS_DIR)
    file(GLOB_RECURSE IMGUI_BINDING_CANDIDATES
            "${CMAKE_BINARY_DIR}/**/imgui_impl_glfw.cpp")

    if (IMGUI_BINDING_CANDIDATES)
        list(REMOVE_DUPLICATES IMGUI_BINDING_CANDIDATES)

        set(_FOUND_DIR "")
        foreach(_cand ${IMGUI_BINDING_CANDIDATES})
            get_filename_component(_dir "${_cand}" DIRECTORY)
            if (EXISTS "${_dir}/imgui_impl_opengl3.cpp")
                set(_FOUND_DIR "${_dir}")
                break()
            endif()
        endforeach()

        if (NOT _FOUND_DIR)
            get_filename_component(_FOUND_DIR "${IMGUI_BINDING_CANDIDATES}" DIRECTORY)
        endif()

        set(AIECAD_IMGUI_BINDINGS_DIR "${_FOUND_DIR}" CACHE PATH "" FORCE)
        message(STATUS "Found ImGui backends: ${AIECAD_IMGUI_BINDINGS_DIR}")
    else()
        message(FATAL_ERROR "Could not find imgui_impl_glfw.cpp in ${CMAKE_BINARY_DIR}")
    endif()
endif()

list(APPEND aiecad_base_files ${src_files} ${header_files})

add_library(aiecad_lib STATIC
        ${aiecad_base_files}
        ${CMAKE_CURRENT_BINARY_DIR}/aiecad/aiecad-config.h
        "${AIECAD_IMGUI_BINDINGS_DIR}/imgui_impl_glfw.cpp"
        "${AIECAD_IMGUI_BINDINGS_DIR}/imgui_impl_opengl3.cpp"
)

target_include_directories(aiecad_lib
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
        "${AIECAD_IMGUI_BINDINGS_DIR}"
)

target_link_libraries(aiecad_lib PUBLIC aiecad_deps)

target_compile_definitions(aiecad_lib PRIVATE
        IMGUI_IMPL_OPENGL_LOADER_GLAD
        IMGUI_ENABLE_DOCKING
)

if (AIECAD_BUILD_TESTS)
    include(AIECAD_Tests)
endif ()

if (AIECAD_BUILD_SANDBOX)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/sandbox")
    aiecad_build_sandbox()
endif ()

add_executable(aiecad_app main.cpp)
target_link_libraries(aiecad_app PRIVATE aiecad_lib)