#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Board
{
    int32_t rows[5][5];
    bool called[5][5];
    bool won;
} Board;

int32_t sum_of_uncalled(Board* board)
{
    int32_t sum = 0;
    for (int r = 0; r < 5; ++r)
    {
	for (int c = 0; c < 5; ++c)
	{
	    if (!board->called[r][c])
	    {
		sum += board->rows[r][c];
	    }
	}
    }
    return sum;
}

void print_board(Board* board)
{
    for (int r = 0; r < 5; ++r)
    {
        for (int c = 0; c < 5; ++c)
        {
            printf("%d(%d)\t", board->rows[r][c], board->called[r][c]);
        }
        printf("\n");
    }
}

bool is_winner(Board* board)
{
    // Nothing clever...

    bool won;
    // Horizontal
    for (int r = 0; r < 5; ++r)
    {
        won = true;
        for (int c = 0; c < 5; ++c)
        {
            won &= board->called[r][c];
        }
        if (won)
        {
            return true;
        }
    }
    // Vertical
    for (int c = 0; c < 5; ++c)
    {
        won = true;
        for (int r = 0; r < 5; ++r)
        {
            won &= board->called[r][c];
        }
        if (won)
        {
            return true;
        }
    }
#if 0
    // Diagonal R
    {
        won = true;
        for (int i = 0; i < 5; ++i)
        {
            won &= board->called[i][i];
        }
        if (won)
        {
            return true;
        }
    }

    // Diagonal L
    {
        won = true;
        for (int i = 0; i < 5; ++i)
        {
            won &= board->called[i][4-i];
        }
	if (won)
	{
	    return true;
	}
    }
#endif
    return false;
}

void update_board(int32_t call, Board* board)
{
    for (int r = 0; r < 5; ++r)
    {
        for (int c = 0; c < 5; ++c)
        {
            if (call == board->rows[r][c])
            {
                board->called[r][c] = true;
                return;
            }
        }
    }
}

void parse_line(char* line, int32_t* values)
{
    char* context = NULL;
    char* token = strtok_r(line, " ", &context);
    int32_t count = 0;
    while (NULL != token)
    {
        values[count] = atoi(token);
        count++;
        token = strtok_r(NULL, " ", &context);
    }
}

void build_board(char** lines, Board* board)
{
    for (int i = 0; i < 5; ++i)
    {
        parse_line(lines[i], board->rows[i]);
    }
}

void parse_moves(char* input, int32_t** moves, int32_t* move_count)
{
    char* context = NULL;
    int32_t mparse[strlen(input)];
    char* token = strtok_r(input, ",", &context);
    int num_moves = 0;
    while (NULL != token)
    {
        mparse[num_moves] = atoi(token);
        num_moves++;
        token = strtok_r(NULL, ",", &context);
    }
    *move_count = num_moves;
    *moves = malloc(num_moves * sizeof(int32_t));
    memmove(*moves, mparse, num_moves * sizeof(int32_t));
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

    int32_t line_count = 0;
    int32_t* moves = NULL;
    int32_t move_count = 0;

    char* board_lines[100][5];
    int32_t board_start = 0;
    int32_t board_end = 0;
    int32_t board_count = 0;
    int32_t board_line = 0;
    while ((read = getline(&buf, &buflen, fh)) != -1)
    {
        if (line_count == 0)
        {
            parse_moves(buf, &moves, &move_count);
        }
        else
        {
            if (strcmp(buf, "\n") == 0)
            {
                board_start = line_count + 1;
                board_end = line_count + 6;
                board_line = 0;
                board_count++;
            }
            if (line_count >= board_start && line_count <= board_end)
            {
                board_lines[board_count-1][board_line++] = strdup(buf);
            }
        }
        line_count++;
    }

    Board* boards = calloc(board_count, sizeof(Board));
    for (int i = 0; i < board_count; ++i)
    {
        build_board(board_lines[i], &boards[i]);
        for (int l = 0; l < 5; ++l)
        {
            free(board_lines[i][l]);
        }
    }

	int32_t winning_number = 0;
    int32_t winning_board = 0;
	int32_t win_order[board_count];
	int32_t winning_numbers[board_count];
    int32_t winners = 0;

    for (int i = 0; i < move_count; ++i)
    {
        for (int b = 0; b < board_count; ++b)
        {
	    if (!boards[b].won)
	    {
		update_board(moves[i], &boards[b]);
		if (is_winner(&boards[b]))
		{
		    boards[b].won = true;
		    winning_number = moves[i];
		    winning_board = b;
		    win_order[winners] = b;
		    winning_numbers[winners] = winning_number;
		    winners++;
		}
	    }
        }
    }

	printf("Problem 1: %d\n", winning_numbers[0] * sum_of_uncalled(&boards[win_order[0]]));
	printf("Problem 2: %d\n", winning_number * sum_of_uncalled(&boards[winning_board]));

    free(buf);
    fclose(fh);

    return EXIT_SUCCESS;
}
