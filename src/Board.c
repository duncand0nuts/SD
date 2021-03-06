#include <stdio.h>
#include <stdlib.h>

#include "../include/Board.h"
#include "../include/Game.h"

/*
*
*  This source file contains functions to initilise and delete the board and its secondary data structures.
*
*/

//  This function creates a new point which stores its own coordinate and state.

point_type *newPoint(int a, int b)
{
	point_type *point = (point_type*)malloc(sizeof(point_type));
	if(!point)
	{
		printf("\nInsufficient memory to allocate for 'point' in function 'newPoint'.\
		Application terminated.");
		exit(-1);
	}
	point->x = a;
	point->y = b;
	point->state = EMPTY;
	return point;
}

//  This function frees the memory allocated to a point after use.

void deletePoint(point_type *point)
{
	free(point);
}

//  This function generates a data structure which stores the coordinates of all possible 4-in-a-row
//  piece combinations on the board.

point_type ***generateConsecutiveLines(point_type ***grid)
{
	int i;
	int count = 0;
	int y;
	int x;
	int t;

	point_type ***lines = (point_type ***)malloc(69 * sizeof(point_type **));
	if(!lines)
	{
		printf("\nInsufficient memory to allocate for 'lines' in function 'generateConsecutiveLines'.\
		Application terminated.");
		exit(-1);
	}

	for(i = 0; i < 69; i++)
	{
		lines[i] = (point_type **)malloc(4 * sizeof(point_type *));
		if(!lines)
		{
			printf("\nInsufficient memory to allocate for 'lines[%d]' in function 'generateConsecutiveLines'.\
			Application terminated.", i);
			exit(-1);
		}
	}

	for(y = 0; y < 6; y++)
	{
		for(x = 0; x < 4; x++)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("\nInsufficient memory to allocate for 'temp' in function 'generateConsecutiveLines'.\
				Application terminated.");
				exit(-1);
			}
			for(i = x; i < (x+4); i++)
			{
				temp[i-x] = grid[i][y];
			}
		lines[count] = temp;
		count++;
		}
	}

	for(x = 0; x < 7; x++)
	{
		for(y = 0; y < 3; y++)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("\nInsufficient memory to allocate for 'temp' in function 'generateConsecutiveLines'.\
				Application terminated.");
				exit(-1);
			}

			for(i = y; i < (y+4); i++)
			{
				temp[i-y] = grid[x][i];
			}

			lines[count] = temp;
			count++;
		}
	}

	for(x = 0; x < 4; x++)
	{
		for(y = 0; y < 3; y++)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("\nInsufficient memory to allocate for 'temp' in function 'generateConsecutiveLines'.\
				Application terminated.");
				exit(-1);
			}

			for(t = x, i = y; (t < (x+4) && i < (y+4)); t++, i++)
			{
				temp[i-y] = grid[t][i];
			}

			lines[count] = temp;
			count++;
		}
	}


	for(x = 0; x < 4; x++)
	{
		for(y = 5; y > 2; y--)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			for(t = x, i = y; (t < (x+4) && i > -1); t++, i--)
			{
				temp[t-x] = grid[t][i];
			}

			lines[count] = temp;
			count++;
		}
	}

	return lines;
}

//  This function frees the memory allocated for the board data structure.

void deleteBoard(board_type *board)
{
	free(board->consecutive_lines);
	free(board->grid);
	free(board->heights);
	free(board->moves);
	free(board);
}

//  This function creates the board data structure.

board_type *createBoard(int a, int b)
{ 
	int x;
	int y;

	board_type *board = (board_type *)malloc(sizeof(board_type));
	if(!board)
	{
		printf("\nInsufficient memory to allocate for 'board' in function 'createBoard'.\
		Application terminated.");
		exit(-1);
	}
		
	board->cols = a;
	board->rows = b;
	board->moves_made = -1;
	board->current_player = PLAYER_ONE;
	board->heights = (int *)malloc(board->cols * sizeof(int));
	if(!board->heights)
	{
		printf("\nInsufficient memory to allocate for 'heights' in function 'createBoard'.\
		Application terminated.");
		exit(-1);
	}

	board->grid = (point_type ***)malloc(board->cols * sizeof(point_type **));
	if(!board->grid)
	{
		printf("\nInsufficient memory to allocate for 'grid' in function 'createBoard'.\
		Application terminated.");
		exit(-1);
	}

	for(x = 0; x < board->cols; x++)
	{
		board->grid[x] =(point_type **)malloc(board->rows * sizeof(point_type *));
		if(!board->grid)
		{
			printf("\nInsufficient memory to allocate for 'grid' in function 'createBoard'.\
			Application terminated.");
			exit(-1);
		}

		board->heights[x] = 0;
		for(y = 0; y < board->rows; y++)
		{
			board->grid[x][y] = newPoint(x,y); 
		}
	}

	board->moves = (int *)malloc(board->cols * board->rows * sizeof(int));
	if(!board->moves)
	{
		printf("\nInsufficient memory to allocate for 'moves' in function 'createBoard'.\
		Application terminated.");
		exit(-1);
	}

	board->consecutive_lines = generateConsecutiveLines(board->grid);
	return board;
}





