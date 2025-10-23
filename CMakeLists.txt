cmake_minimum_required(VERSION 4.0)

project(Maelstrom
    VERSION 3.0.7
    DESCRIPTION "Maelstrom"
    HOMEPAGE_URL https://github.com/libsdl-org/Maelstrom
    LANGUAGES C CXX
)

# options

option(BUILD_TESTS "Build the tests" ON)
option(BUILD_DOC "Build the documentation" OFF)
option(BUILD_MACRES "Build the macres executable" OFF)
option(BUILD_PLAYWAVE "Build the playwave executable" OFF)
option(BUILD_SND2WAVE "Build the snd2wave executable" OFF)
option(BUILD_MAELSTROM_NETD "Build the Maelstrom-netd executable" OFF)

# if using valgrind, set BUILD_WITH_ASAN to OFF
option(BUILD_WITH_ASAN "Build with ASAN" ON)

if(BUILD_TESTS)
include(CTest)
# enable_testing()
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)

add_subdirectory(maclib)
add_subdirectory(netlogic)
add_subdirectory(screenlib)

# misc library

set(target misc)
add_library(${target} STATIC)
target_include_directories(${target} PRIVATE
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
    checksum.cpp
    controls.cpp
    dialog.cpp
    fastrand.cpp
    init.cpp
    load.cpp
    myerror.cpp
    netscore.cpp
    rect.cpp
    scores.cpp
)

# Maelstrom executable

set(target Maelstrom)

add_executable(${target})
target_compile_definitions(${target} PRIVATE
-DPACKAGE="Maelstrom"
-DVERSION="3.0.7"
-D_REENTRANT
)

target_sources(${target} PRIVATE
    main.cpp

    # checksum.cpp
    # controls.cpp
    # dialog.cpp
    # fastrand.cpp
    # init.cpp
    # load.cpp
    # myerror.cpp
    # netscore.cpp
    # rect.cpp
    # scores.cpp
)


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
if(BUILD_WITH_ASAN)
    target_compile_options(${target} PRIVATE -fsanitize=address)
    target_link_options(${target} PRIVATE -fsanitize=address)
endif()
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


# target_compile_options(${target} PRIVATE -fsanitize=address)
# target_link_options(${target} PRIVATE -fsanitize=address)

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



# Maelstrom-netd

if(BUILD_MAELSTROM_NETD)
set(target Maelstrom-netd)
add_executable(${target})
target_compile_features(${target} PRIVATE c_std_23)
target_include_directories(${target} PRIVATE
    ${CMAKE_SOURCE_DIR}/netlogic
)
target_sources(${target} PRIVATE
    Maelstrom-netd.c
)
endif()

# tests

if(BUILD_TESTS)
add_subdirectory(tests)
endif()

# documentation

if(BUILD_DOC)
add_subdirectory(dev/doxygen)
endif()

# valgrind target

set(target Maelstrom)
add_custom_target(valgrind
    COMMAND valgrind
        --leak-check=full
        --show-leak-kinds=all
        --track-origins=yes
        -s --suppressions=${CMAKE_SOURCE_DIR}/Maelstrom.valgrind.supp
        --gen-suppressions=all
        --log-file=${CMAKE_SOURCE_DIR}/dev/valgrind/logs/memcheck.log
        $<TARGET_FILE:${target}>
    DEPENDS ${target}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${target}>
    COMMENT "Running Maelstrom with valgrind"
)
