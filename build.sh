#!/bin/bash
set -e # stop if any errors

{
    cd "$(dirname "$0")" # This ensures that the stuff is ran at the directory where this script lives

    # making a "build" file and determining the location of the vcpkg root
    # use $env:VCPKG_ROOT = "the location in your PC" manually to set up the vcpkg root

    # this is to force my system to use vcpkg since it isn't working normally.
    cmake -G "Unix Makefiles" -B build -S . \
        -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
        -DVCPKG_TARGET_TRIPLET=x64-mingw-static \
        -DCMAKE_MAKE_PROGRAM=mingw32-make

    # generating and executing build
    cmake --build ./build
}

exec $(dirname "$0")/build/claude-code "$@"

# I suck at shell scripts
