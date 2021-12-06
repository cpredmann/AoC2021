#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int64_t fish_count[9] = {0};
    int64_t fish_buf[9] = {0};

    while ((read = getline(&buf, &buflen, fh)) != -1)
    {
        char* context = NULL;
        char* token = strtok_r(buf, ",", &context);
        while (NULL != token)
        {
            fish_count[atoi(token)]++;
            token = strtok_r(NULL, ",", &context);
        }
    }

    int32_t days = 256;
    int32_t p1_days = 80;
    int64_t num_fish = 0;
    for (int i = 0; i < days; ++i)
    {
        for (int f = 0; f < 8; ++f)
        {

            fish_buf[f] = fish_count[f+1];
            if (f == 0)
            {
                fish_buf[8] = fish_count[0];
            }

        }
        fish_buf[6] += fish_buf[8];
        memcpy(fish_count, fish_buf, 9 * sizeof(int64_t));
        memset(fish_buf, 0, 9 * sizeof(int64_t));
        if (i == (p1_days - 1))
        {
            for (int i = 0; i < 9; ++i)
            {
                num_fish += fish_count[i];
            }
        }
    }
    int64_t num_fish_2 = 0;
    for (int i = 0; i < 9; ++i)
    {
        num_fish_2 += fish_count[i];
    }


    printf("Problem 1: %lld\n", num_fish);
    printf("Problem 2: %lld\n", num_fish_2);

    free(buf);
    fclose(fh);

    return EXIT_SUCCESS;
}
