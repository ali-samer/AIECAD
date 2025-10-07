# FindXRT.cmake
# Usage: find_package(XRT REQUIRED)
# Provides: XRT::coreutil (required), plus XRT_INCLUDE_DIR and XRT_ROOT

set(XRT_ROOT "" CACHE PATH "Root of XRT install (contains include/ and lib or lib64/)")
set(XRT_ROOT_HINT "${XRT_ROOT}")
if (NOT XRT_ROOT_HINT AND DEFINED ENV{XILINX_XRT})
    set(XRT_ROOT_HINT "$ENV{XILINX_XRT}")
endif()
if (NOT XRT_ROOT_HINT AND EXISTS "/opt/xilinx/xrt")
    set(XRT_ROOT_HINT "/opt/xilinx/xrt")
endif()

find_path(XRT_INCLUDE_DIR
        NAMES xrt/xrt_device.h xrt/xrt_bo.h xrt/xrt_kernel.h
        HINTS
            "${XRT_ROOT_HINT}/include"
            "${XRT_ROOT_HINT}"
        DOC "XRT include directory"
        PATH_SUFFIXES include
)

set(_XRT_LIB_HINTS
        "${XRT_ROOT_HINT}/lib"
        "${XRT_ROOT_HINT}/lib64"
)

find_library(XRT_COREUTIL NAMES xrt_coreutil HINTS ${_XRT_LIB_HINTS})

find_program(XRT_XBUTIL NAMES xbutil HINTS "${XRT_ROOT_HINT}/bin")
find_program(XRT_SMICLI NAMES xrt-smi HINTS "${XRT_ROOT_HINT}/bin")

# Standardized way for writing custom cmake modules
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(XRT
        REQUIRED_VARS XRT_INCLUDE_DIR XRT_COREUTIL
        FAIL_MESSAGE "XRT not found. Set XRT_ROOT  or source /opt/xilinx/xrt/setup.sh."
)

add_library(XRT::coreutil SHARED IMPORTED)
set_target_properties(XRT::coreutil PROPERTIES
        IMPORTED_LOCATION "${XRT_COREUTIL}"
        INTERFACE_INCLUDE_DIRECTORIES "${XRT_INCLUDE_DIR}"
)

get_filename_component(_XRT_LIBDIR "${XRT_COREUTIL}" DIRECTORY)
set(XRT_ROOT "${XRT_ROOT_HINT}" CACHE PATH "XRT root" FORCE)
set(XRT_LIBDIR "${_XRT_LIBDIR}"  CACHE PATH "XRT libdir" FORCE)
mark_as_advanced(XRT_INCLUDE_DIR XRT_COREUTIL XRT_XBUTIL XRT_SMICLI XRT_LIBDIR)
