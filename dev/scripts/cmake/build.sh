#!/bin/bash

cd "$WORKSPACE_ROOT"
clear
set -ex

# clean up

git clean -dxf
git reset --hard HEAD

# if [ -d build ]; then rm -rf build; fi
# https://learn.microsoft.com/en-us/vcpkg/users/buildsystems/cmake-integration
# cmake -S . -B build -GNinja -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT"/scripts/buildsystems/vcpkg.cmake
cmake -S . -B build -GNinja -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT"/scripts/buildsystems/vcpkg.cmake --graphviz=dev/graphviz/Maelstrom.dot
# cmake -S . -B build -GNinja
(cd build; ninja)
