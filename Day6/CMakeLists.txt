add_executable(
    Day6
    Problems.c
    )

add_test(
    NAME
    Day6Input
    COMMAND
    Day6 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    )
