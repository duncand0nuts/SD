#include <stdio.h>
#include <stdlib.h>

#include "../include/IO.h"

/*
*
*  This source file contains the function which generates the array of 'char's
*  which represents the game board.  
*
*/

//  This function takes the board data structure and represents it in a format ready for
//  printing to screen.

char *charsBoard(board_type *board)
{
	int y;
	int x;
	int state;
	char *temp = (char *)malloc(board->rows * (board->cols + 1) * sizeof(char) + 1);
	char *curr = temp;
	if(!temp)
	{
		printf("\nInsufficient memory to allocate for 'temp' in function 'charsBoard'.\
		Application terminated.");
		exit(-1);
	}

	for(y = board->rows-1; y > -1; y--)
	{
		for(x = 0; x < board->cols; x++)
		{
			state = getState(board->grid[x][y]);

			if(state == EMPTY)
			*curr = '-';

			else if(state == PLAYER_ONE)
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
