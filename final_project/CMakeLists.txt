cmake_minimum_required(VERSION 3.15)
project(final_project)

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

add_executable(final_project main.cpp Botan.cpp Botan.h SharedQueue.h BruteForceIterator.cpp BruteForceIterator.h)
enable_warnings_for(final_project)
target_link_libraries(final_project Botan::botan)

add_subdirectory(test)