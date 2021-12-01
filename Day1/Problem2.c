#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    FILE* fh = fopen(argv[1], "ra");
    if (NULL == fh)
    {
        fprintf(stderr, "%s could not be opened\n", argv[1]);
        return EXIT_FAILURE;
    }

    char line[128];
    int32_t prev_sum = INT32_MIN;
    int32_t cur_sum = 0;
    int32_t sum_counter = 0;

    int32_t counter = 0;



    while (fgets(line, 128, fh) != NULL)
    {
        int32_t val = atoi(line);
        if (sum_counter < 3)
        {
            cur_sum += val;
            sum_counter++;
        }
        else
        {
            if (prev_sum != INT32_MIN && cur_sum > prev_sum)
            {
                counter++;
            }
            prev_sum = cur_sum;
            cur_sum = 0;
            sum_counter = 0;
        }
    }

    fclose(fh);

    printf("Increased %d times\n", counter);
    return EXIT_SUCCESS;

}
