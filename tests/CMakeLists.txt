option(BUILD_CATCH_EXAMPLES "Build the catch examples" OFF)

if(BUILD_CATCH_EXAMPLES)
add_subdirectory(examples)
endif()

add_subdirectory(game_loop)
