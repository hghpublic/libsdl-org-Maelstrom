
# libSDLmac
set(target SDLmac)
add_library(${target} STATIC)
target_include_directories(${target} PRIVATE
    ${CMAKE_SOURCE_DIR}/screenlib
)
target_link_libraries(${target} PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,
        SDL2::SDL2,
        SDL2::SDL2-static>
)
target_sources(${target} PRIVATE
    Mac_FontServ.cpp
    Mac_Resource.cpp
    Mac_Sound.cpp
    Mac_Wave.cpp
)

# macres

if(BUILD_MACRES)
set(target macres)
add_executable(${target})
target_compile_features(${target} PRIVATE cxx_std_23)
target_link_libraries(${target} PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,
        SDL2::SDL2,
        SDL2::SDL2-static>
)
target_sources(${target} PRIVATE
    macres.cpp

    Mac_Resource.cpp
)
endif()

# playwave

if(BUILD_PLAYWAVE)
set(target playwave)
add_executable(${target})
target_compile_features(${target} PRIVATE cxx_std_23)
target_link_libraries(${target} PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,
        SDL2::SDL2,
        SDL2::SDL2-static>
)
target_sources(${target} PRIVATE
    playwave.cpp

    Mac_Resource.cpp
    Mac_Wave.cpp
)
endif()

# snd2wav

if(BUILD_SND2WAVE)
set(target snd2wav)
add_executable(${target})
target_compile_features(${target} PRIVATE cxx_std_23)
target_link_libraries(${target} PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,
        SDL2::SDL2,
        SDL2::SDL2-static>
)
target_sources(${target} PRIVATE
    snd2wav.cpp

    Mac_Resource.cpp
    Mac_Wave.cpp
)
endif()
