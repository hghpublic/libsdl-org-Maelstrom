cmake_minimum_required(VERSION 4.1)

project(01-drawing-lines C)

find_package(SDL3 CONFIG REQUIRED)

set(target 01-drawing-lines)
add_executable(${target} drawing-lines.c)
target_compile_features(${target} PRIVATE c_std_23)
target_link_libraries(${target} PRIVATE SDL3::SDL3)
set_target_properties(${target} PROPERTIES 
    SUFFIX ".html"
    OUTPUT_NAME "index"
    LINK_FLAGS "-sEXIT_RUNTIME=1"
)

add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_SOURCE_DIR}/serve.py
        $<TARGET_FILE_DIR:${target}>/)  

add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_SOURCE_DIR}/favicon.ico
        $<TARGET_FILE_DIR:${target}>/)
