

# test_misc library

set(target test_misc)
add_library(${target} STATIC)
target_include_directories(${target} PRIVATE
    ${CMAKE_SOURCE_DIR}/
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
    test_init.cpp
    
    ${CMAKE_SOURCE_DIR}/checksum.cpp
    ${CMAKE_SOURCE_DIR}/controls.cpp
    ${CMAKE_SOURCE_DIR}/dialog.cpp
    ${CMAKE_SOURCE_DIR}/fastrand.cpp
    # init.cpp
    ${CMAKE_SOURCE_DIR}/load.cpp
    ${CMAKE_SOURCE_DIR}/myerror.cpp
    ${CMAKE_SOURCE_DIR}/netscore.cpp
    ${CMAKE_SOURCE_DIR}/rect.cpp
    ${CMAKE_SOURCE_DIR}/scores.cpp
)
