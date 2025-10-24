option(USE_CMAKE_GOOGLE_TEST_INTEGRATION "If enabled, use the google test integration included in CMake." ON)

find_package(GMock MODULE REQUIRED)
find_package(GTest MODULE REQUIRED)
if (USE_CMAKE_GOOGLE_TEST_INTEGRATION)
    include(GoogleTest OPTIONAL RESULT_VARIABLE HAVE_CMAKE_GTEST)
    enable_testing()
else ()
    set(HAVE_CMAKE_GTEST OFF)
endif ()

add_library(aiecad_test_support
    ${AIECAD_DIR}/test/common/TestMain.cpp
)

target_compile_definitions(aiecad_test_support
    PUBLIC
        ${LIBGMOCK_DEFINES}
)

target_include_directories(aiecad_test_support
    SYSTEM
    PUBLIC
        ${LIBGMOCK_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(aiecad_test_support
    PUBLIC
        aiecad_lib
        aiecad_deps
        ${LIBGMOCK_LIBRARIES}
)

include(cmake/utils/Functions.cmake)

aiecad_define_tests(
    DIRECTORY test/
        TEST dummy_calc_test SOURCES CalcTest.cpp
)

# =============================================================================
#  aiecad_define_tests — Custom test (and benchmark) registration helper
# =============================================================================
#
# ORIGIN & LICENSE
# ----------------
# This function is ADAPTED from Meta’s Folly project (folly_define_tests)
# under the Apache License 2.0.
# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at:
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# IMPLEMENTATION REFERENCE
# ------------------------
# The behavior documented here corresponds to the function body provided
# in cmake/utils/Functions.cmake (definition of `aiecad_define_tests`).
#
#
# OVERVIEW
# --------
# aiecad_define_tests() lets you declare unit tests (and optional benchmarks)
# in a concise, declarative way, very similar to Folly’s usage. You supply one
# or more DIRECTORY blocks. Inside each DIRECTORY block you list TEST and/or
# BENCHMARK entries, each with optional TAGS (like SLOW, WINDOWS_DISABLED) and
# optional HEADERS/SOURCES/CONTENT_DIR sections.
#
# The function will:
#   - create an executable for each TEST/BENCHMARK,
#   - (for TEST) register with CTest (using gtest_add_tests() when available),
#   - group sources for IDEs (source_group),
#   - copy optional CONTENT_DIR alongside the binary,
#   - link each target with aiecad_test_support,
#   - honor tag- and platform-gated skips,
#   - set a 120s timeout and run tests with WORKING_DIRECTORY="${TOP_DIR}".
#
#
# SYNTAX (tokens & ordering)
# --------------------------
#   aiecad_define_tests(
#     DIRECTORY <relative/test/root/>                # repeatable
#       TEST <target_name> [<TAGS> ...]              # repeatable inside DIRECTORY
#         [HEADERS <rel/header1> <rel/header2> ...]
#         [SOURCES <rel/source1> <rel/source2> ...]
#         [CONTENT_DIR <relative/content/dir>]
#       [BENCHMARK <target_name> [<TAGS> ...]
#         [HEADERS ...] [SOURCES ...] ]
#     [DIRECTORY ...]
#   )
#
# IMPORTANT ORDERING RULES (matches the parser in tmp.txt)
# - After TEST or BENCHMARK and the <name>, you may supply zero or more TAGS.
#   Valid tags: BROKEN, HANGING, SLOW, WINDOWS_DISABLED, APPLE_DISABLED.
# - After tags, you may open a HEADERS or SOURCES section (in any order).
#   Once in a section, subsequent bare tokens are treated as paths for that
#   section until another keyword appears (HEADERS, SOURCES, CONTENT_DIR,
#   TEST, BENCHMARK, or DIRECTORY).
# - CONTENT_DIR takes a single path token after it.
# - Newlines are purely cosmetic; tokens can span multiple lines. This matches
#   Folly’s style where SOURCES may be introduced on a new line and list
#   multiple files across multiple lines.
#
#
# PATH RESOLUTION
# ---------------
# All HEADERS/SOURCES/CONTENT_DIR paths are interpreted relative to the
# DIRECTORY base and are automatically prefixed with:
#   "${AIECAD_DIR}/${<DIRECTORY>}${<RELATIVE_PATH>}"
#
# Example:
#   DIRECTORY aiecad/aiecad/test/
#     TEST my_test
#       SOURCES Foo/BarTest.cpp
# resolves to:
#   ${AIECAD_DIR}/aiecad/aiecad/test/Foo/BarTest.cpp
#
#
# TAG/OPTION SEMANTICS
# --------------------
# - BROKEN           : skip unless -DAIECAD_BUILD_BROKEN_TESTS=ON
# - HANGING          : skip unless -DAIECAD_BUILD_HANGING_TESTS=ON
# - SLOW             : skip unless -DAIECAD_BUILD_SLOW_TESTS=ON
# - WINDOWS_DISABLED : on WIN32, skip unless -DAIECAD_BUILD_WINDOWS_DISABLED=ON
# - APPLE_DISABLED   : on APPLE, skip unless -DAIECAD_BUILD_APPLE_DISABLED=ON
# - Benchmarks       : built only if -DAIECAD_BUILD_BENCHMARKS=ON
#
#
# TEST REGISTRATION & RUNTIME
# ---------------------------
# add_executable(<name> ...headers... ...sources...)
# If HAVE_CMAKE_GTEST is ON:
#   gtest_add_tests(TARGET <name> TEST_PREFIX "<name>." WORKING_DIRECTORY "${TOP_DIR}")
#   set TIMEOUT=120 on the generated cases.
# Else:
#   add_test(NAME <name> COMMAND <name> WORKING_DIRECTORY "${TOP_DIR}")
#   set TIMEOUT=120 on the single test.
#
# CONTENT_DIR handling:
#   - configure-time copy into: ${CMAKE_CURRENT_BINARY_DIR}/aiecad/${DIRECTORY}${CONTENT_DIR}
#   - POST_BUILD copy alongside binary: $<TARGET_FILE_DIR:<name>>/aiecad/${DIRECTORY}${CONTENT_DIR}
#
# IDE organization:
#   - source_group("" FILES <all headers+sources in a DIRECTORY>)
#   - strip trailing "test/" from DIRECTORY to create IDE folder:
#       set_property(TARGET <name> PROPERTY FOLDER "Tests/${strippedDir}")
#
# Linking:
#   target_link_libraries(<name> PRIVATE aiecad_test_support)
#
#
# AIECAD TEST TREE & MAIN OVERRIDE
# --------------------------------
# Conventionally, all tests live under: aiecad/aiecad/test/
# A shared weak main() is provided at: aiecad/aiecad/test/common/TestMain.cpp
# (AIECAD_ATTR_WEAK). Provide your own strong main() in a test target if you
# need custom initialization before RUN_ALL_TESTS().
#
#
# USAGE EXAMPLES (Folly-style multi-line form)
# --------------------------------------------
# The following mirrors Folly’s style you referenced, but with AIECAD paths.
#
# aiecad_define_tests(
#   DIRECTORY aiecad/aiecad/test/
#     TEST aiecad_algorithm_simd_any_of_test
#       SOURCES algorithm/simd/detail/SimdAnyOfTest.cpp
#     TEST aiecad_algorithm_simd_for_each_test
#       SOURCES algorithm/simd/detail/SimdForEachTest.cpp
#
#   DIRECTORY aiecad/aiecad/test/chrono/
#     TEST aiecad_chrono_conv_test WINDOWS_DISABLED
#       SOURCES ConvTest.cpp
#
#   DIRECTORY aiecad/aiecad/test/container/
#     BENCHMARK aiecad_container_fbvector_benchmark
#       SOURCES FBVectorBenchmark.cpp
#       HEADERS FBVectorBenchmarks.cpp.h
#     TEST aiecad_container_fbvector_test
#       SOURCES FBVectorTest.cpp
#     TEST aiecad_container_small_vector_test WINDOWS_DISABLED
#       SOURCES small_vector_test.cpp
#
#   DIRECTORY aiecad/aiecad/test/detail/base64_detail/
#     TEST aiecad_detail_base64_detail_test WINDOWS_DISABLED
#     SOURCES
#       Base64AgainstScalarTest.cpp
#       Base64PlatformTest.cpp
#       Base64SpecialCasesTest.cpp
# )
#
# Notes on the example:
# - Tags (e.g., WINDOWS_DISABLED) appear right after the TEST name, before
#   HEADERS/SOURCES; this matches the parser’s “tags first, then sections”
#   contract.
# - HEADERS and SOURCES may span multiple lines for readability.
# - Multiple DIRECTORY blocks can be specified in a single invocation.
#
#
# COMMON PITFALLS
# ---------------
# - Forgetting that HEADERS/SOURCES paths are relative to the active DIRECTORY.
# - Placing HEADERS/SOURCES before the TEST name (not allowed).
# - Misspelling a tag or keyword (HEADERS/SOURCES/CONTENT_DIR); unknown tokens
#   cause a hard error (message(FATAL_ERROR ...)).
# - Expecting tests to register when HAVE_CMAKE_GTEST is OFF and assuming
#   per-test-case discovery; in that mode, each executable is one CTest test.
#
#
# QUICK CHECKLIST
# ---------------
# [ ] Add or locate a DIRECTORY block for your test subtree (ending with "test/").
# [ ] Append a TEST <name> [<tags>...] entry.
# [ ] Add SOURCES (and optional HEADERS, CONTENT_DIR).
# [ ] Configure with any needed toggles (-DAIECAD_BUILD_SLOW_TESTS=ON, etc.).
# [ ] Build & run: ctest --output-on-failure (or from your IDE).
#
# End of documentation.