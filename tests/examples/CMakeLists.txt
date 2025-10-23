
# this is heuristically generated, and may not be correct
find_package(Catch2 CONFIG REQUIRED)

set(tests
    test_factorial
    test_fibonacci
    test_vector
)

foreach(test ${tests})
set(target ${test})
add_executable(${target} ${target}.cpp)
target_link_libraries(${target} PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endforeach()
