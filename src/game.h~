#ifndef __GAME_H
#define __GAME_H

#include <stdio.h>
#include <stdlib.h>

static const int PLAYER_ONE = 1;
static const int PLAYER_TWO = -1;
static const int EMPTY = 0;

typedef struct point point_type;
typedef struct board board_type;

struct point {
	int x, y, state;
} ;

struct board {

	point_type ***grid;
	int *heights;

	int cols;
	int rows;

	int *moves;
	int moves_made;

	int current_player;
	point_type ***consecutive_lines;
} ;

#endif
