#!/bin/sh

git clean -dxf

# https://developer.mozilla.org/en-US/docs/WebAssembly/Guides/C_to_Wasm

# https://emscripten.org/docs/api_reference/emscripten.h.html#c.emscripten_force_exit

# em++ -std=c++23 -sEXIT_RUNTIME hello.cpp -o hello.html

EMSDK_ROOT=/workspaces/libsdl-org-Maelstrom/dev/emscripten/emsdk
emcmake cmake -S . -B build -GNinja \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT"/scripts/buildsystems/vcpkg.cmake \
    -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=${EMSDK_ROOT}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake \
    -DVCPKG_TARGET_TRIPLET=wasm32-emscripten

cmake --build build
