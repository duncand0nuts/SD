#ifndef __BOARD_H
#define __BOARD_H

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

point_type *newPoint(int a, int b);

void deletePoint(point_type *point);

point_type ***generateConsecutiveLines(point_type ***grid);

board_type *createBoard(int a, int b);

void deleteboard(board_type *board);

#endif
