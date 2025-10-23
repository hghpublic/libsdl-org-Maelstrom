

set(target logic)
add_library(${target} STATIC)
target_include_directories(${target} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/maclib
    ${CMAKE_SOURCE_DIR}/netlogic
    ${CMAKE_SOURCE_DIR}/screenlib
)
target_link_libraries(${target} PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,
        SDL2::SDL2,
        SDL2::SDL2-static>
)
target_sources(${target} PRIVATE
    about.cpp
    blit.cpp
    game.cpp
    logic.cpp
    make.cpp
    netplay.cpp
    object.cpp
    objects.cpp
    player.cpp
)
