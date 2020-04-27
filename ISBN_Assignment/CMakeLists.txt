cmake_minimum_required(VERSION 3.15)
project(ISBN_Assignment)

# Add path for custom modules
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Ideally the next line would be uncommented, but with it present, it can fail on Cygwin on Windows
# see https://github.com/google/googletest/issues/813
set(CMAKE_CXX_EXTENSIONS OFF)

include(CompilerSetup)
# Compiler Flags
set(GCC_WARNINGS "-Wall -Wextra -Wpedantic -Wunused -Wformat=2 -Wswitch-enum -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wcast-align -Wcast-qual -Wconversion -Wsign-conversion -Wzero-as-null-pointer-constant -Wlogical-op -Wmissing-declarations -Wctor-dtor-privacy -Wnoexcept -Wnon-virtual-dtor -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wredundant-decls -Wshadow -Wwrite-strings -Wno-long-long")
set(CLANG_WARNINGS "-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-documentation-unknown-command")


set(CLANG_DEBUG "-O0 -g")
set(CLANG_RELEASE "-O3")

set(GCC_DEBUG "-O0 -g")
set(GCC_RELEASE "-O3")


# Set up the compiler flags used
if(CMAKE_COMPILER_IS_GNUCXX)
    # gcc
    set(CMAKE_CXX_FLAGS "${GCC_WARNINGS}")

    set(CMAKE_CXX_FLAGS_DEBUG "${GCC_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${GCC_RELEASE}")
else()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # clang
        set(CMAKE_CXX_FLAGS "${CLANG_WARNINGS}")

        set(CMAKE_CXX_FLAGS_DEBUG "${CLANG_DEBUG}")
        set(CMAKE_CXX_FLAGS_RELEASE "${CLANG_RELEASE}")
    else()
        # Generic flags for undetected compiler
        set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
        set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    endif()
endif()

add_executable(ISBN_Assignment main.cpp ISBN.cpp ISBN.h)

enable_warnings_for(ISBN_Assignment)

add_subdirectory(test)