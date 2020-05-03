include(GetGoogletest)
include(GoogleTest)

add_executable(unit_tests ../midterm.h ../midterm.cpp midterm.cpp midterm.h midterm.cpp midterm.h)
target_link_libraries(unit_tests
        GTest::gtest
        GTest::gtest_main
        )
enable_warnings_for(unit_tests)

# Googletest's headers trigger some warnings we don't care about
if ("${CMAKE_CXX_COMPILER_ID}}" MATCHES "Clang")
    target_compile_options(unit_tests PRIVATE -Wno-global-constructors)
endif ()

# Can either tell CTest about every single unit test, or only
# tell it about the test executable
#add_test(unit_tests ${CMAKE_BINARY_DIR}/unit_tests)
gtest_discover_tests(unit_tests)