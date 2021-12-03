add_executable(
    Day2
    Problems.c
    )

add_test(
    NAME
    Day2Test
    COMMAND
    Day2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)
