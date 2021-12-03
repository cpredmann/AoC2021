add_executable(
    Day4
    Problems.c
    )

add_test(
    NAME
    Day4Input
    COMMAND
    Day4 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    )
