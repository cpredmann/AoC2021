add_executable(
    Day1
    Problems.c
    )

add_test(
    NAME
    Day1Test
    COMMAND
    Day1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)
