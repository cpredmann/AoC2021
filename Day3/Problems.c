#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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

    int32_t* ones = NULL;
    int32_t* zeroes = NULL;
    int32_t len = 0;
    int32_t lines = 0;
    while ((read = getline(&buf, &buflen, fh)) != -1)
    {
        if (NULL == ones)
        {
            len = read - 1;
            ones = (int32_t*)calloc(len, sizeof(int32_t));
            zeroes = (int32_t*)calloc(len, sizeof(int32_t));
        }
        int32_t count = 0;
        while (count < len)
        {
            char c = buf[count];
            if (c == '0')
            {
                zeroes[count] += 1;
            }
            else
            {
                ones[count] += 1;
            }
            count++;
        }
        lines++;
    }
    int32_t gamma = 0;
    for (int i = 0; i < len; ++i)
    {
        gamma <<= 1;
        gamma |= ones[i] > zeroes[i];
    }
    int32_t epsilon = gamma ^ (int32_t)(pow(2, len) - 1);
    printf("Problem 1: %d\n", gamma * epsilon);

    rewind(fh);

    char* oxygen[lines];
    char* scrubber[lines];
    int32_t scrubber_count = lines;
    int32_t oxygen_count = lines;
    lines = 0;
    while ((read = getline(&buf, &buflen, fh)) != -1)
    {
        oxygen[lines] = strdup(buf);
        scrubber[lines] = strdup(buf);
        lines++;
    }

    for (int i = 0; i < len; ++i)
    {
        int32_t scrubber_zeroes = 0;
        int32_t scrubber_ones = 0;
        int32_t oxygen_zeroes = 0;
        int32_t oxygen_ones = 0;
        for (int j = 0; j < lines; ++j)
        {
            if (oxygen[j] != NULL)
            {
                if (oxygen[j][i] == '0')
                {
                    oxygen_zeroes++;
                }
                else
                {
                    oxygen_ones++;
                }
            }
            if (scrubber[j] != NULL)
            {
                if (scrubber[j][i] == '0')
                {
                    scrubber_zeroes++;
                }
                else
                {
                    scrubber_ones++;
                }
            }
        }
        for (int j = 0; j < lines; ++j)
        {
            if (oxygen[j] != NULL && oxygen_count > 1)
            {
                if (oxygen_ones >= oxygen_zeroes)
                {
                    if (oxygen[j][i] == '0')
                    {
                        free(oxygen[j]);
                        oxygen[j] = NULL;
                        oxygen_count--;
                    }
                }
                else
                {
                    if (oxygen[j][i] == '1')
                    {
                        free(oxygen[j]);
                        oxygen[j] = NULL;
                        oxygen_count--;
                    }
                }
            }
            if (scrubber[j] != NULL && scrubber_count > 1)
            {
                if (scrubber_ones >= scrubber_zeroes)
                {
                    if (scrubber[j][i] == '1')
                    {
                        free(scrubber[j]);
                        scrubber[j] = NULL;
                        scrubber_count--;
                    }
                }
                else
                {
                    if (scrubber[j][i] == '0')
                    {
                        free(scrubber[j]);
                        scrubber[j] = NULL;
                        scrubber_count--;
                    }
                }
            }
        }
    }


    int32_t scrubber_val = 0;
    int32_t oxygen_val = 0;

    for (int i = 0; i < lines; ++i)
    {
        if (scrubber[i] != NULL)
        {
            if (scrubber_val == 0)
            {
                for (int j = 0; j < len; ++j)
                {
                    scrubber_val <<= 1;
                    scrubber_val |= (int)(scrubber[i][j] == '1');
                }
            }
            free(scrubber[i]);
        }
        if (oxygen[i] != NULL)
        {
            if (oxygen_val == 0)
            {
                for (int j = 0; j < len; ++j)
                {
                    oxygen_val <<= 1;
                    oxygen_val |= (int)(oxygen[i][j] == '1');
                }
            }
            free(oxygen[i]);
        }
    }

    printf("Problem 2: %d\n", oxygen_val * scrubber_val);

    free(ones);
    free(zeroes);
    free(buf);
    fclose(fh);

    return EXIT_SUCCESS;
}
