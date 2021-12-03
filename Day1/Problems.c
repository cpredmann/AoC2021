#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int32_t prev_value_1 = INT_FAST32_MIN;
    int32_t increases_1 = 0;

    int32_t sums[3] = { 0, 0, 0 };
    int32_t count = 0;
    int32_t prev_value_2 = INT_FAST32_MIN;
    int32_t increases_2 = 0;

    while ((read = getline(&buf, &buflen, fh)) != -1)
    {
        int32_t cur_value = atoi(buf);
        if (prev_value_1 > INT_FAST32_MIN && cur_value > prev_value_1)
        {
            increases_1++;
        }
        prev_value_1 = cur_value;

        int32_t window = 0;
        while (window < 3)
        {
            sums[window] += count < window ? 0 : cur_value;
            window++;
        }
        if (count > 1)
        {
            int32_t cur_window = (count - 2) % 3;
            int32_t win_value = sums[cur_window];
            sums[cur_window] = 0;
            if (prev_value_2 > INT_FAST32_MIN && win_value > prev_value_2)
            {
                increases_2++;
            }
            prev_value_2 = win_value;
        }
        count++;
    }
    printf("Problem 1: %d\n", increases_1);
    printf("Problem 2: %d\n", increases_2);


    free(buf);
    fclose(fh);

    return EXIT_SUCCESS;
}
