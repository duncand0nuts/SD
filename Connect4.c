#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

#include "include/Game.h"
#include "include/Board.h"
#include "include/IO.h"
#include "include/CPU_player.h"

/*
*
*  This is the main source file for the Connect4 project and gives a high level description
*  of the program structure and function.  For help on how to compile and run the program,
*  please see README.txt.
*
*/

int main(int argc, char** argv) 
{
	int input;
	int difficulty;

	srand (time(NULL));  //  Initialise random seed

	board_type *board = createBoard(7,6);

	printf("\nWelcome to Connect4!\n");
	printf("\nFor help and other information please see the readme file.\n");
	printf("\nTo play a game, please select a difficulty level by entering the corresponding\
	\n number from the list below:\n");
	printf("1 - Easy\n");
	printf("2 - Medium\n");
	printf("3 - Hard\n");

	scanf("%d",&difficulty);

	while(difficulty < 1 || difficulty > 3)  //  Check that difficulty selection is in allowed bounds
	{
		printf("\nYou have entered an invalid value.  Please select again:");
		scanf("%d",&difficulty);
	}

	switch(difficulty)  //  Modify 'difficulty' variable based on selection
	{
		case 1 :
			difficulty = 5;
			break;
		case 2 :
			difficulty = 2;
			break;
		case 3 :
			difficulty = 1;
			break;
	}

	printf("\nMake moves by entering values from 1 - 7 to select which column to drop a piece into.\n");

	//  This is the main event loop for the program, where turns are taken and moves are made:

	while((winnerIs(board) == 0) && validMovesLeft(board))
 	{
		if(getCurrentPlayer(board) == PLAYER_ONE)  //  Player move section
		{
			printf("\nIt's your turn!  Make a move...\n");
			scanf("%d", &input);

			while(input < 1 || input > 7)   //  Test that move is into a valid column
			{
				printf("\nYou have made an invalid move! Please make a move by selecting a column number between 1 and 7.\n");
				scanf("%d",&input);
			}
		
			while(board->heights[input-1] == 6)  //  Test that column is not full
			{
				printf("\nThe column you have selected is full!  Please select another:\n");
				scanf("%d",&input);
			}

 			makeMove(board,input-1); //  Implements chosen move provided that it is valid
		}

 		else  //  Computer move section
		{
			printf("\nIt's the computer player's turn!  Please wait...\n");

			//  Here the 'difficulty' variable is used to determine whether a random or reasoned move is made.
			//  If a more difficult setting is chosen, a reasoned move will be made more often.

			if(rand() % difficulty == 0)  
			{
				makeMove(board, getReasonedMove(board)); 
			}
			
			else
			{
				makeMove(board, getRandomPlayerMove(board));			
			}
		}	
	
		printf("%s\n", charsBoard(board));

	}

	//  Print message according to how game transpired:

	if(!validMovesLeft(board)) //  No winner
	{
		printf("\nThere are no moves left.  It's a tie!\n");
	}
	else if (winnerIs(board) == 1)  //  Player victory
	{
		printf("\nYou won!  Congratulations!\n");
	}
	else  //  CPU victory
	{
		printf("\nYou lost!  Better luck next time!\n");
	}

 	return 0;

}


