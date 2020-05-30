# -*- cmake -*-

#[=======================================================================[.rst:
GetBotan
-------

Downloads and configures Botan library using the FetchContent CMake module.

Depending on updates to CMake and/or Botan this may need to update. Additionally,
this approach downloads Botan from Github and a network connection may not always
be acceptable

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets:

``Botan::botan``
  The botan library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``botan_POPULATED``
  True if Googletest has been downloaded and configured

#]=======================================================================]


include(FetchContent)
FetchContent_Declare(
        botan
        GIT_REPOSITORY https://github.com/randombit/botan.git
        GIT_TAG 2.14.0
)

FetchContent_GetProperties(botan)
string(TOLOWER "botan" lcName)
if(NOT ${lcName}_POPULATED)
    # This downloads botan, but nothing beyond that
    # Ideally we would also use a CONGIFURE step to avoid the extra
    # ExternalProject, but that is explicitly not supported
    FetchContent_Populate(botan)

    include(ExternalProject)
    set(botan_args
            --minimized-build
            --enable-modules=hash,bcrypt,scrypt,hex,system_rng,sha2_64,sha3,argon2
            --disable-shared
            --prefix=${CMAKE_CURRENT_BINARY_DIR}/botan
            )

    ExternalProject_Add(botan_project
            SOURCE_DIR ${${lcName}_SOURCE_DIR}
            BINARY_DIR ${${lcName}_BINARY_DIR}
            UPDATE_COMMAND "" # Don't need to update since using tagged release
            CONFIGURE_COMMAND python ${${lcName}_SOURCE_DIR}/configure.py ${botan_args}
            BUILD_COMMAND make
            BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/botan/lib/libbotan-2.a
            )

    add_library(Botan::botan STATIC IMPORTED GLOBAL)
    add_dependencies(Botan::botan botan_project)

    # Workaround for INTERFACE_INCLUDE_DIRECTORIES. The problem is the include
    # directory needs to exist at cmake configuration time even though it won't
    # exist until the external project is checked out at build time.
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/botan/include/botan-2)

    set_target_properties(Botan::botan PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/botan/lib/libbotan-2.a
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/botan/include/botan-2
            )
endif()
