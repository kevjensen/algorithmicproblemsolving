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
# set(CMAKE_CXX_EXTENSIONS OFF)

include(CompilerSetup)
add_executable(ISBN_Assignment main.cpp)

enable_warnings_for(ISBN_Assignment)

add_subdirectory(test)