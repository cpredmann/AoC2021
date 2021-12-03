#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void problem_2(char* direction, int32_t value, int32_t* horizontal, int32_t* depth, int32_t* aim)
{
    if (strcmp(direction, "down") == 0)
    {
        *aim += value;
    }
    else if (strcmp(direction, "up") == 0)
    {
        *aim -= value;
    }
    else if (strcmp(direction, "forward") == 0)
    {
        *horizontal += value;
        *depth += (*aim) * value;
    }
}

void problem_1(char* direction, int32_t value, int32_t* horizontal, int32_t* depth)
{
    if (strcmp(direction, "forward") == 0)
    {
        *horizontal += value;
    }
    else if (strcmp(direction, "up") == 0)
    {
        *depth -= value;
    }
    else if (strcmp(direction, "down") == 0)
    {
        *depth += value;
    }
    else
    {
        fprintf(stderr, "Not matched: %s %d\n", direction, value);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        return EXIT_FAILURE;
    }
    FILE* fh;
    if ((fh = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Failed to open: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    size_t buflen = 0;
    char* buf = NULL;
    ssize_t read = 0;

    const char* space = " ";
    char* token;
    char* context = NULL;
    size_t token_ct = 0;

    char* direction = NULL;
    int32_t value = 0;

    int32_t horiz_1 = 0;
    int32_t depth_1 = 0;

    int32_t horiz_2 = 0;
    int32_t depth_2 = 0;
    int32_t aim = 0;

    while ((read = getline(&buf, &buflen, fh)) != -1)
    {
        token = strtok_r(buf, space, &context);
        while (token != NULL)
        {
            if (token_ct == 0)
            {
                direction = token;
            }
            else if (token_ct == 1)
            {
                value = atoi(token);
            }
            token = strtok_r(NULL, space, &context);
            token_ct++;
        }
        token_ct = 0;
        problem_1(direction, value, &horiz_1, &depth_1);
        problem_2(direction, value, &horiz_2, &depth_2, &aim);
    }
    printf("Problem 1 value = %d\n ", horiz_1 * depth_1);
    printf("Problem 2 value = %d\n ", horiz_2 * depth_2);
    free(buf);
    fclose(fh);

    return EXIT_SUCCESS;
}
