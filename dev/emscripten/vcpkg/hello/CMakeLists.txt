cmake_minimum_required(VERSION 4.1)

project(hello CXX)

set(target hello)

find_package(fmt CONFIG REQUIRED)

add_executable(${target} hello.cpp)
target_compile_features(${target} PRIVATE cxx_std_23)
target_link_libraries(${target} PRIVATE fmt::fmt)
# https://emscripten.org/docs/api_reference/emscripten.h.html#c.emscripten_force_exit
set_target_properties(${target} PROPERTIES 
    SUFFIX ".html"
    OUTPUT_NAME "index"
)

add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_SOURCE_DIR}/serve.py
        $<TARGET_FILE_DIR:${target}>/)  
