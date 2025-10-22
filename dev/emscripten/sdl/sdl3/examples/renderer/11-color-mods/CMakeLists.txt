cmake_minimum_required(VERSION 4.1)

project(11-color-mods C)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

set(target 11-color-mods)
add_executable(${target} color-mods.c)
target_compile_features(${target} PRIVATE c_std_23)
target_link_libraries(${target} PRIVATE SDL3::SDL3)
target_link_libraries(${target} PRIVATE SDL3_image::SDL3_image-static)
set_target_properties(${target} PROPERTIES 
    SUFFIX ".html"
    OUTPUT_NAME "index"
    LINK_FLAGS "-sEXIT_RUNTIME=1 --embed-file sample.png"
)

add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_SOURCE_DIR}/serve.py
        $<TARGET_FILE_DIR:${target}>/)  

add_custom_command(TARGET ${target} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_SOURCE_DIR}/assets/sample.png
        ${CMAKE_BINARY_DIR}/)  
    
add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_SOURCE_DIR}/favicon.ico
        $<TARGET_FILE_DIR:${target}>/)
