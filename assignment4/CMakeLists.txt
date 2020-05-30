cmake_minimum_required(VERSION 3.15)
project(assignment4)
# Add path for custom modules
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Ideally the next line would be uncommented, but with it present, it can fail on Cygwin on Windows
# see https://github.com/google/googletest/issues/813
# set(CMAKE_CXX_EXTENSIONS OFF)

include(CompilerSetup)
include(GetBotan)

add_executable(assignment4 main.cpp Botan.cpp BruteForceIterator.cpp BruteForceIterator.h Botan.h BruteForceHash.cpp BruteForceHash.h)

enable_warnings_for(assignment4)
target_link_libraries(assignment4 Botan::botan)

add_subdirectory(test)