add_executable(
    Day7
    Problems.c
    )

add_test(
    NAME
    Day7Input
    COMMAND
    Day7 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    )
