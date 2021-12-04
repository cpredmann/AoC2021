add_executable(
    Day5
    Problems.c
    )

add_test(
    NAME
    Day5Input
    COMMAND
    Day5 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    )
