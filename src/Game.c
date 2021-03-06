#include <stdio.h>
#include <stdlib.h>

#include "../include/Game.h"

/*
*
*  This source file contains functions which manipulate the game board or
*  provide information about the state of the board or game.
*
*/

//  This function tests if two pointers point to the same board square.

int equalsPosition(point_type *a, point_type *b)
{
	return ((a->x == b->x) && (a->y == b->y));
}

//  This function sets the state of a point on the board according to 
//  what it is passed as an argument.

void setState(point_type *a, int player)
{
	a->state = player;
}

//  This function returns the state of the board square pointed to by a pointer.

int getState(point_type *a)
{
	return (a->state);
}

//  This function assesses whether a given move is valid or not.

int validMove(board_type *board, int column)
{
	return board->heights[column] < board->rows;
}

//  This function implements a move by updating the board data structure.

void makeMove(board_type *board, int column)
{
	int height = board->heights[column];

	setState(board->grid[column][height], board->current_player);
	board->heights[column]++;
	board->moves_made++;
	board->moves[board->moves_made] = column;
	board->current_player = -board->current_player;
}

//  This function reverses the changes made to the board made by makeMove (above).

void undoMove(board_type *board)
{
	int moves = board->moves[board->moves_made];
	
	setState(board->grid[moves][board->heights[moves]-1],(EMPTY));
	board->heights[moves]--;
	board->moves_made--;
	board->current_player = -board->current_player;
}

//  This function returns the number of valid moves remaining on the board.

int validMovesLeft(board_type *board)
{
	return (board->moves_made < ((board->cols * board->rows)-1));
}

//  This function returns a 'score' based on how many of the possible 4-in-a-row
//  lines they have placed pieces in, which are still possible to use to win the game.  
//  If both players have placed pieces in a row, it will return 0.

int getScore(point_type *points[]) 
{
	int playerone=0;
	int playertwo=0;
	int i;
	int state;

	for(i = 0; i < 4; i++)
	{
		state = getState(points[i]);

		if(state == PLAYER_ONE)
		playerone++;

		else if(state == PLAYER_TWO)
		playertwo++;
	}

	if((playerone + playertwo > 0) && (!(playerone > 0 && playertwo > 0)))
	{
		if(playerone != 0) 
		{
			return playerone;
		}
		else
		{
			return -playertwo;
		}
	}

	else
	return 0;
}

//  This function returns distinct values if either player wins, or 0 if not.

int winnerIs(board_type *board)
{
	int i;
	int score;

	for(i = 0; i<69; i++)
	{
		score = getScore(board->consecutive_lines[i]);

		if(score == 4)
		{
		return PLAYER_ONE;
		}
		else if(score == -4)
		{
		return PLAYER_TWO;
		}
	}

	return 0;

}

//  This function returns a value which indicates which player is currently 
//  taking their turn.

int getCurrentPlayer(board_type *board)
{
return board->current_player;
}


