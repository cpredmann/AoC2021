#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "No input specified\n");
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

    int32_t sub_position[1000];
    int32_t sub_count = 0;

    int32_t max_val = INT32_MIN;
    int32_t min_val = INT32_MAX;

    while ((read = getline(&buf, &buflen, fh)) != -1)
    {
        char* context = NULL;
        char* token = strtok_r(buf, ",", &context);
        while (NULL != token)
        {
            sub_position[sub_count] = strtoll(token, NULL, 10);
            max_val = fmax(max_val, sub_position[sub_count]);
            min_val = fmin(min_val, sub_position[sub_count]);
            token = strtok_r(NULL, ",", &context);
            sub_count++;
        }
    }

    int32_t move_range = max_val - min_val + 1;
    int32_t sub_moves[sub_count][move_range];
    for (int i = 0; i < sub_count; ++i)
    {
        for (int j = 0; j < move_range; ++j)
        {
            sub_moves[i][j] = abs(min_val + j - sub_position[i]);
        }
    }
    int32_t min_moves = INT32_MAX;
    for (int i = 0; i < move_range; ++i)
    {
        int32_t sum = 0;
        for (int j = 0; j < sub_count; ++j)
        {
            sum += sub_moves[j][i];
        }
        if (sum < min_moves)
        {
            min_moves = sum;
        }
    }

    int32_t sum_cache[move_range];
    for (int i = 0; i < move_range; ++i)
    {
        if (i > 0)
        {
            sum_cache[i] = sum_cache[i-1] + i;
        }
    }
    int32_t p2_min_moves = INT32_MAX;
    for (int i = 0; i < move_range; ++i)
    {
        int32_t sum = 0;
        for (int j = 0; j < sub_count; ++j)
        {
            int32_t moves = sub_moves[j][i];
            sum += sum_cache[moves];
        }
        if (sum < p2_min_moves)
        {
            p2_min_moves = sum;
        }
    }

    printf("Problem 1: %d\n", min_moves);
    printf("Problem 2: %d\n", p2_min_moves);

    free(buf);
    fclose(fh);

    return EXIT_SUCCESS;
}
