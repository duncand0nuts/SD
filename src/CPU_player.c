#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/CPU_player.h"

int getRandomPlayerMove(board_type *board)
{
	int val =-1;
	int possible[7];
	int i;

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
		int rad = rand() % 7;
		if(possible[rad] == 1)
		{
			val = rad;
		}
	}
	
	return val;
}


// should return a number
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

// don't change this unless you understand it
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


//careful with this
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
			
			if(moves[i]<moves[highest])
			{
				highest=i;
			}	

			undoMove(board);
		}

	}

	return moves[highest];

}
