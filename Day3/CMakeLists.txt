add_executable(
    Day3
    Problems.c
    )

add_test(
    NAME
    Day3Input
    COMMAND
    Day3 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    )
