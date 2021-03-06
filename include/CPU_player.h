#ifndef __CPU_PLAYER_H
#define __CPU_PLAYER_H

#include "Game.h"

int getRandomPlayerMove(board_type *board);

int getReasonedMove(board_type *board);

int minValue(board_type *board, int ply);

int maxValue(board_type *board, int ply);

#endif
