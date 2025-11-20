
if (NOT DEFINED IS_AARCH64_ARCH AND ${CMAKE_SYSTEM_PROCESSOR} MATCHES "^(aarch64|arm64|AMD64)$")
    set(IS_AARCH64_ARCH TRUE)
endif ()

if (NOT DEFINED IS_X86_64_ARCH AND ${CMAKE_SYSTEM_PROCESSOR} MATCHES "^(x86_64)")
    set(IS_X86_64_ARCH TRUE)
endif ()

if (DEFINED IS_X86_64_ARCH OR DEFINED IS_AARCH64_ARCH)
    message(STATUS "Architecture detected: ${CMAKE_SYSTEM_PROCESSOR}")
else ()
    message(FATAL_ERROR "Archicture detected is not supported: ${CMAKE_SYSTEM_PROCESSOR}")
endif ()

if (APPLE)
    message(STATUS "Building on Apple platform")

    find_library(METAL_FRAMEWORK Metal)
    if (METAL_FRAMEWORK)
        message(STATUS "Metal framework found: ${METAL_FRAMEWORK}")
        set(AIECAD_RENDER_API_OPENGL ON)
        set(AIECAD_RENDER_API_METAL ON)
    else ()
        message(STATUS "Metal framework not found – Metal disabled")
        set(AIECAD_RENDER_API_OPENGL ON)
    endif ()
endif ()