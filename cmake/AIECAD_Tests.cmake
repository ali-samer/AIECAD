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