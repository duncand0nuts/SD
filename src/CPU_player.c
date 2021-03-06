#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/CPU_player.h"

/*
*
*  This source file contains functions relating to the computer player's decision making.
*
*/

//  This function selects a column to place a piece in at random.

int getRandomPlayerMove(board_type *board)
{
	int val =-1;
	int possible[7];
	int i;
	int random_move;

	for(i = 0; i < 7; i++)
	{
		if(validMove(board,i))
		{
			possible[i] = 1;
		}

		else
		{
			possible[i] = 0;
		}
	}

	while(val == -1)
	{
		random_move = rand() % 7;
		if(possible[random_move] == 1)
		{
			val = random_move;
		}
	}
	
	return val;
}


//  This function returns a move based on analyses of each possible move.
//  It will select a move which maximises the chance of future victory for the CPU player.

int getReasonedMove(board_type *board)
{
	int moves[7];
	int highest = 0;
	int i;

	for(i = 0; i < 7; i++)
	{
		moves[i] = INT_MIN;
		if(validMove(board, i))
		{
			makeMove(board,i);
			moves[i] = minValue(board,4);

			if(moves[i] >= moves[highest])
			{
				highest=i;
			}

			undoMove(board);
		} 
	}
	return highest;
}

//  These next two functions, minValue and maxValue call each other recursively depending
//  on the value of 'ply'passed to them.  They assess the strength of moves.

int minValue(board_type *board, int ply)
{
	int moves[7];
	int lowest = 0;
	int i;

	for(i = 0; i < 7; i++)
	{
		moves[i] = INT_MAX;
		if(validMove(board,i))
		{
			makeMove(board,i);
			if((winnerIs(board) == 0) && ply > 0)
			{
				moves[i] = maxValue(board,ply-1);
			}

			else 
			{
				moves[i] = -getStrength(board);
			}

			if(moves[i] < moves[lowest])
			{
				lowest=i;
			}

			undoMove(board);
		}

	}

	return moves[lowest];

}

int maxValue(board_type *board, int ply)
{
	int moves[7];
	int highest = 0;
	int i;
	for(i = 0; i < 7; i++)
	{
		moves[i] = INT_MAX;
		if(validMove(board,i))
		{
			makeMove(board,i);
			if((winnerIs(board) == 0) && ply>0)
			{
				moves[i] = minValue(board,ply-1);
			}

			else 
			{
				moves[i] = -getStrength(board);
			}
			
			if(moves[i] < moves[highest])
			{
				highest=i;
			}	

			undoMove(board);
		}

	}

	return moves[highest];

}

//  This function returns a number based on the 'score' returned by 'getScore' which is
//  used by the previous two functions to help pick a good move.

int getStrength(board_type *board)
{
	int sum = 0;
	int weights[] = {0,1,10,50,600};
	int i;
	int score;

	for( i=0;i<69;i++)
	{
		score = getScore(board->consecutive_lines[i]);

		sum += (score > 0) ? weights[abs(score)]:-weights[abs(score)];
	}

	return sum + (board->current_player == PLAYER_ONE ? 16 : -16);
}

