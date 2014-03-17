#include <stdio.h>
#include <stdlib.h>

#include "../include/IO.h"

char *toString(board_type *board)
{
	char *temp = (char *)malloc(board->rows * (board->cols + 1) * sizeof(char) + 1);
	char *curr = temp;
	int y;
	int x;

	for(y = board->rows-1; y > -1; y--)
	{
		for(x = 0; x < board->cols; x++)
		{
			if(getState(board->grid[x][y]) == EMPTY)
			*curr = '-';

			else if(getState(board->grid[x][y]) == PLAYER_ONE)
			*curr = 'O';

			else
			*curr = 'X';

			curr++;
		}
		*curr = '\n';
		curr++;
		}
	return temp;
}
