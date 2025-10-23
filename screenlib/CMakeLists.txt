
set(target SDLscreen)
add_library(${target} STATIC)

target_link_libraries(${target} PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,
        SDL2::SDL2,
        SDL2::SDL2-static>
)

target_sources(${target} PRIVATE
    pixel.cpp
    SDL_FrameBuf.cpp
)
