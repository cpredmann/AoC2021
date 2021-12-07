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

    while ((read = getline(&buf, &buflen, fh)) != -1)
    {
    }
    //printf("Problem 1: %d\n", increases_1);
    //printf("Problem 2: %d\n", increases_2);

    free(buf);
    fclose(fh);

    return EXIT_SUCCESS;
}
