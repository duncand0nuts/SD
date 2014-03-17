#ifndef __GAME_H
#define __GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "Board.h"

static const int PLAYER_ONE = 1;
static const int PLAYER_TWO = -1;
static const int EMPTY = 0;

int equalsPosition(point_type *a, point_type *b);

void setState(point_type *a, int player);

int getState(point_type *a);

int validMove(board_type *board, int column);

void makeMove(board_type *board, int column);

void undoMove(board_type *board);

int validMovesLeft(board_type *board);

int getScore(point_type *points[]);

int getStrength(board_type *board);

int winnerIs(board_type *board);

int getCurrentPlayer(board_type *board);
 
#endif
