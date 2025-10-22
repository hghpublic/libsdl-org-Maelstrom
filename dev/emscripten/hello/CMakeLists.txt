cmake_minimum_required(VERSION 4.1)

project(hello CXX)

set(target hello)
# set(CMAKE_EXECUTABLE_SUFFIX ".html")

add_executable(${target} hello.cpp)
target_compile_features(${target} PRIVATE cxx_std_23)
# https://emscripten.org/docs/api_reference/emscripten.h.html#c.emscripten_force_exit
set_target_properties(${target} PROPERTIES 
    SUFFIX ".html"
    OUTPUT_NAME "index"
    LINK_FLAGS "-sEXIT_RUNTIME=1"
)

add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_SOURCE_DIR}/serve.py
        $<TARGET_FILE_DIR:${target}>/)  
