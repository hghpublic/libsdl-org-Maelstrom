#!/bin/sh

git clean -dxf

# https://developer.mozilla.org/en-US/docs/WebAssembly/Guides/C_to_Wasm

# https://emscripten.org/docs/api_reference/emscripten.h.html#c.emscripten_force_exit

# em++ -std=c++23 -fexperimental-library -sEXIT_RUNTIME hello.cpp -o hello.html
# em++ -std=c++23 -sEXIT_RUNTIME hello.cpp -o hello.html

emcmake cmake -S . -B build -GNinja    
cmake --build build
