cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Setting C++ standard to c++${CMAKE_CXX_STANDARD}")

set(CMAKE_MODULE_PATH
        "${CMAKE_MODULE_PATH}"
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

project(swag
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
set(CMAKE_INSTALL_DIR lib/cmake/swag CACHE STRING
        "The subdirectory where CMake configuration files should be installed"
)

include(settings/ProjectOptions)
swag_set_options()

set(TOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SWAG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/swag")
string(REGEX REPLACE "(.)" [[\\\1]] SWAG_DIR_REGEX_ESCAPED "${SWAG_DIR}")

include(checks/SwagPlatformChecks)
include(utils/SwagAutoSource)

swag_auto_source(
        OUT_VAR             src_files
        DIRECTORIES         "${SWAG_DIR}"
        EXCLUDE_DIRECTORIES "${SWAG_DIR}/test"
        EXTENSIONS          cpp
        TRAVERSE            RECURSE
        FAIL_MODE           FATAL_ERROR
)

swag_auto_source(
        OUT_VAR             header_files
        DIRECTORIES         "${SWAG_DIR}"
        EXCLUDE_DIRECTORIES "${SWAG_DIR}/test"
        EXTENSIONS          h hpp
        TRAVERSE            RECURSE
        FAIL_MODE           FATAL_ERROR
)

include(ProjectDeps)
include(checks/SwagConfigs)

add_library(swag_deps INTERFACE)

if (SWAG_INCLUDE_DIRS)
    target_include_directories(swag_deps INTERFACE ${SWAG_INCLUDE_DIRS})
endif()
if (SWAG_LINK_LIBS)
    target_link_libraries(swag_deps INTERFACE ${SWAG_LINK_LIBS})
endif()
if (SWAG_COMPILE_OPTS)
    target_compile_options(swag_deps INTERFACE ${SWAG_COMPILE_OPTS})
endif()
if (SWAG_COMPILE_DEFS)
    target_compile_definitions(swag_deps INTERFACE ${SWAG_COMPILE_DEFS})
endif()

if (XRT_LIBDIR)
    set_target_properties(swag_deps PROPERTIES
            BUILD_WITH_INSTALL_RPATH TRUE
            BUILD_RPATH   "${XRT_LIBDIR}"
            INSTALL_RPATH "$ORIGIN;${XRT_LIBDIR}"
    )
endif()

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/swag)
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/swag-config.h.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/swag/swag-config.h"
)

list(APPEND swag_base_files ${src_files} ${header_files})

# Creating a collection of object files are useful for other tasks without recompiling them
add_library(swag_base
    OBJECT
        ${swag_base_files}
        ${CMAKE_CURRENT_BINARY_DIR}/swag/swag-config.h
)

# Setting up include paths for base files
target_include_directories(swag_base
    PRIVATE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_BINARY_DIR}
)

# Main library that'll contain the SWAG generator and other components
add_library(swag_lib
        $<TARGET_OBJECTS:swag_base>
)

target_include_directories(swag_lib INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)



target_link_libraries(swag_lib PUBLIC swag_deps)

if (SWAG_BUILD_TESTS)
    include(SWAG_Tests)
endif ()

add_executable(swag_app main.cpp)
target_link_libraries(swag_app  PRIVATE swag_lib)