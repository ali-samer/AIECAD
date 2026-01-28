include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)
include(CheckCXXSourceRuns)

if (CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*")
    list(APPEND AIECAD_CXX_FLAGS -Wno-psabi)
endif ()

if (NOT CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    check_include_file_cxx(jemalloc/jemalloc.h AIECAD_USE_JEMALLOC)
endif ()

if (MSVC)
    set(AIECAD_HAVE_WEAK_SYMBOLS OFF CACHE BOOL "" FORCE)
else()
    set(_saved_req_flags         "${CMAKE_REQUIRED_FLAGS}")
    set(_saved_req_link_options  "${CMAKE_REQUIRED_LINK_OPTIONS}")
    set(_saved_req_libs          "${CMAKE_REQUIRED_LIBRARIES}")

    set(CMAKE_REQUIRED_FLAGS "")
    set(CMAKE_REQUIRED_LINK_OPTIONS "")
    set(CMAKE_REQUIRED_LIBRARIES "")
    if (APPLE)
        set(CMAKE_REQUIRED_LINK_OPTIONS "-Wl,-undefined,dynamic_lookup")
    endif ()

    check_cxx_source_runs([[
        extern "C" int func_undefined_weak_symbols(void)
        #if defined(__APPLE__) && defined(__MACH__)
            __attribute__((weak_import))
        #else
            __attribute__((weak))
        #endif
        ;
        int main() {
            if (&func_undefined_weak_symbols) {
                return func_undefined_weak_symbols();
            } else {
            return 0;
            }
        }]] AIECAD_HAVE_WEAK_SYMBOLS)

    set(CMAKE_REQUIRED_FLAGS         "${_saved_req_flags}")
    set(CMAKE_REQUIRED_LINK_OPTIONS  "${_saved_req_link_options}")
    set(CMAKE_REQUIRED_LIBRARIES     "${_saved_req_libs}")
endif()

