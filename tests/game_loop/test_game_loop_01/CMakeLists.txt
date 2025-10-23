

# this is heuristically generated, and may not be correct
find_package(Catch2 CONFIG REQUIRED)


# https://cmake.org/cmake/help/latest/command/target_link_libraries.html#cyclic-dependencies-of-static-libraries
# Cyclic Dependencies of Static Libraries

target_link_libraries(logic PRIVATE SDLmac)

# test_game_loop_01 executable

set(target test_game_loop_01)
add_executable(${target} ${target}.cpp ../test_main.cpp)
target_link_libraries(${target} PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
target_compile_features(${target} PRIVATE cxx_std_23)
target_include_directories(${target} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/maclib
    ${CMAKE_SOURCE_DIR}/netlogic
    ${CMAKE_SOURCE_DIR}/screenlib
)
target_link_libraries(${target} PRIVATE
    SDLmac
    logic
    SDLscreen
    misc
)
target_link_libraries(${target} PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,
        SDL2::SDL2,
        SDL2::SDL2-static>
)
target_link_libraries(${target} PRIVATE
    $<IF:$<TARGET_EXISTS:SDL2_net::SDL2_net>,
        SDL2_net::SDL2_net,
        SDL2_net::SDL2_net-static>)

add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)

# copy images

add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_SOURCE_DIR}/Images
        $<TARGET_FILE_DIR:${target}>/Images)

# copy assets

set(assets
    Maelstrom_Fonts
    Maelstrom_Sounds
    Maelstrom_Sprites
    icon.bmp
)
foreach(asset ${assets})
add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_SOURCE_DIR}/${asset}
        $<TARGET_FILE_DIR:${target}>/)  
endforeach()


