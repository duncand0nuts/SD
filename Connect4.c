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
 */
int main(int argc, char** argv) {
 srand (time(NULL));
board_type *board = createBoard(7,6);

int input;
while((winnerIs(board)==0) && validMovesLeft(board))
 {
if(getCurrentPlayer(board) == PLAYER_ONE)	
{
scanf("%d", &input);
  makeMove(board,input);// Make it so!
}
 else
 makeMove(board, getReasonedMove(board));// Make it so!

printf("%s\n", toString(board));


}
 return 0;

}


