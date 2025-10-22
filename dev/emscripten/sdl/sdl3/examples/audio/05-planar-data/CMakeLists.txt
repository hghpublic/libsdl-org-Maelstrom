cmake_minimum_required(VERSION 4.1)

project(02-primitives C)

find_package(SDL3 CONFIG REQUIRED)

set(target 02-primitives)
add_executable(${target} primitives.c)
target_compile_features(${target} PRIVATE c_std_23)
target_link_libraries(${target} PRIVATE SDL3::SDL3)
set_target_properties(${target} PROPERTIES 
    SUFFIX ".html"
    OUTPUT_NAME "index"
)

add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_SOURCE_DIR}/serve.py
        $<TARGET_FILE_DIR:${target}>/)  
