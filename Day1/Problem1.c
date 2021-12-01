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
    int32_t prev = INT32_MIN;
    int32_t counter = 0;
    while (fgets(line, 128, fh) != NULL)
    {
        int32_t val = atoi(line);
        if (prev != INT32_MIN && val > prev)
        {
            counter++;
        }
        prev = val;
    }

    fclose(fh);

    printf("Increased %d times\n", counter);
    return EXIT_SUCCESS;

}
