cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Setting C++ standard to c++${CMAKE_CXX_STANDARD}")

set(CMAKE_MODULE_PATH
        "${CMAKE_MODULE_PATH}"
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
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
        EXCLUDE_DIRECTORIES "${AIECAD_DIR}/test"
        EXTENSIONS          cpp
        TRAVERSE            RECURSE
        FAIL_MODE           FATAL_ERROR
)

aiecad_auto_source(
        OUT_VAR             header_files
        DIRECTORIES         "${AIECAD_DIR}"
        EXCLUDE_DIRECTORIES "${AIECAD_DIR}/test"
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
    target_compile_definitions(aiecad_deps INTERFACE ${AIECAD_COMPILE_DEFS})
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

list(APPEND aiecad_base_files ${src_files} ${header_files})

# Creating a collection of object files is useful for other tasks without recompiling them
add_library(aiecad_base
    OBJECT
        ${aiecad_base_files}
        ${CMAKE_CURRENT_BINARY_DIR}/aiecad/aiecad-config.h
)

# Setting up include paths for base files
target_include_directories(aiecad_base
    PRIVATE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_BINARY_DIR}
)

# Main library that'll contain the AIECAD generator and other components
add_library(aiecad_lib
        $<TARGET_OBJECTS:aiecad_base>
)

target_include_directories(aiecad_lib INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)



target_link_libraries(aiecad_lib PUBLIC aiecad_deps)

if (AIECAD_BUILD_TESTS)
    include(AIECAD_Tests)
endif ()

add_executable(aiecad_app main.cpp)
target_link_libraries(aiecad_app  PRIVATE aiecad_lib)