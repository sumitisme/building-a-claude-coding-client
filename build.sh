#!/bin/bash
set -e # stop if any errors

cd "$(dirname "$0")" # This ensures that the stuff is ran at the directory where this script lives

# making a "build" file and determining the location of the vcpkg root
# use $env:VCPKG_ROOT = "the location in your PC" manually to set up the vcpkg root

cmake -G "Unix Makefiles" -B build -S . -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"

# generating and executing build
cmake --build ./build

./build/claude-code "$@"

# I suck at shell scripts
