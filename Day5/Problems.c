#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <regex.h>

typedef struct Line
{
    int32_t x1;
    int32_t y1;
    int32_t x2;
    int32_t y2;
} Line;

void debug_grid(int32_t** grid, int32_t x, int32_t y)
{
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            printf("%d", grid[x][y]);
        }
        printf("\n");
    }
}

regex_t line_regex;
void parse_line(const char* line_str, Line* line)
{
    regmatch_t m[5];
    char matched[10];
    int fail = regexec(&line_regex, line_str, 5, m, 0);
    if (!fail)
    {
        line->x1 = strtoll(&line_str[m[1].rm_so], NULL, 10);
        line->y1 = strtoll(&line_str[m[2].rm_so], NULL, 10);
        line->x2 = strtoll(&line_str[m[3].rm_so], NULL, 10);
        line->y2 = strtoll(&line_str[m[4].rm_so], NULL, 10);
    }
    else
    {
        printf("No match: %s\n", line_str);
    }
}

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

    Line* lines = malloc(1000 * sizeof(Line));
    int32_t line_count = 0;

    int reg = regcomp(&line_regex, "([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)", REG_EXTENDED);

    if (reg)
    {
        fprintf(stderr, "Couldn't compile regex\n");
        return EXIT_FAILURE;
    }

    int32_t max_x = INT32_MIN;
    int32_t max_y = INT32_MIN;
    while ((read = getline(&buf, &buflen, fh)) != -1)
    {
        if (line_count > 1000)
        {
            lines = realloc(lines, line_count * 2 * sizeof(Line));
            printf("reallocating\n");
        }
        parse_line(buf, &lines[line_count]);
        max_x = fmax(fmax(lines[line_count].x1, lines[line_count].x2), max_x);
        max_y = fmax(fmax(lines[line_count].y1, lines[line_count].y2), max_y);
        line_count++;
    }

    max_x++;
    max_y++;
    int32_t** depth_grid = calloc(max_y, sizeof(int32_t));
    for (int i = 0; i < max_y; ++i)
    {
        depth_grid[i] = calloc(max_x, sizeof(int32_t));
    }
    int32_t danger = 0;
    int32_t diag_danger = 0;
    for (int i = 0; i < line_count; ++i)
    {
        Line l = lines[i];
        if (l.x1 == l.x2)
        {
            int32_t start = fmin(l.y1, l.y2);
            int32_t end = fmax(l.y1, l.y2);
            for (int i = start; i <= end; ++i)
            {
                depth_grid[i][l.x1]++;
                if (depth_grid[i][l.x1] == 2)
                {
                    danger++;
                }
            }
        }
        else if (l.y1 == l.y2)
        {
            int32_t start = fmin(l.x1, l.x2);
            int32_t end = fmax(l.x1, l.x2);
            for (int i = start; i <= end; ++i)
            {
                depth_grid[l.y1][i]++;
                if (depth_grid[l.y1][i] == 2)
                {
                    danger++;
                }
            }
        }
    }

    for (int i = 0; i < line_count; ++i)
    {
        Line l = lines[i];
        if ((l.x1 != l.x2) && (l.y1 != l.y2))
        {
            int32_t cur_x = l.x1;
            int32_t cur_y = l.y1;
            int32_t end_x = l.x1 < l.x2 ? l.x2 + 1 : l.x2 - 1;
            int32_t end_y = l.y1 < l.y2 ? l.y2 + 1 : l.y2 - 1;
            while (cur_x != end_x && cur_y != end_y)
            {
                depth_grid[cur_y][cur_x]++;
                if (depth_grid[cur_y][cur_x] == 2)
                {
                    diag_danger++;
                }
                if (l.x1 < l.x2)
                {
                    cur_x++;
                }
                else
                {
                    cur_x--;
                }

                if (l.y1 < l.y2)
                {
                    cur_y++;
                }
                else
                {
                    cur_y--;
                }
            }
        }
    }

    printf("Problem 1: %d\n", danger);
    printf("Problem 2: %d\n", diag_danger + danger);

    free(lines);
    free(buf);
    fclose(fh);

    return EXIT_SUCCESS;
}
