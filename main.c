#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>















board_type * createBoard(int a, int b)
{ 
board_type * p = (board_type*)malloc(sizeof(board_type));
p->cols=a;
p->rows=b;
p->moves_made=-1;
p->current_player=PLAYER_ONE;
p->heights = (int *)malloc(p->cols * sizeof(int));
p->grid = (point_type ***)malloc(p->cols * sizeof(point_type **));
int x;
int y;
for(x = 0; x < p->cols; x++)
{
p->grid[x] =(point_type **)malloc(p->rows * sizeof(point_type *));
p->heights[x] = 0;
for(y = 0; y< p->rows; y++)
{
p->grid[x][y] = newPoint(x,y);
}
}
p->moves = (int *)malloc(p->cols * p->rows * sizeof(int));

p->consecutive_lines = generateConsecutiveLines(p->grid);
return p;
}

void deleteboard(board_type* p)
{
free(p->consecutive_lines);
free(p->grid);
free(p->heights);
free(p->moves);
free(p);
}

int validMove(board_type * b, int column)
{
	return b->heights[column]<b->rows;
}

void makeMove(board_type * b, int column)
{


setState(b->grid[column][b->heights[column]],b->current_player);

b->heights[column]++;
b->moves_made++;
b->moves[b->moves_made]=column;
b->current_player=-b->current_player;
}


void undoMove(board_type * b)
{

setState(b->grid[b->moves[b->moves_made]][b->heights[b->moves[b->moves_made]]-1],(EMPTY));
b->heights[b->moves[b->moves_made]]--;
b->moves_made--;
b->current_player=-b->current_player;
}


int validMovesLeft(board_type * b)
{
return b->moves_made<((b->cols*b->rows)-1);
}

int getScore(point_type * points[]) {

int playerone=0;

int playertwo=0;
int i;
for( i=0;i<4;i++)
if(getState(points[i])==PLAYER_ONE)
playerone++;
else if(getState(points[i])==PLAYER_TWO)
playertwo++;
if((playerone+playertwo>0) && (!(playerone>0 && playertwo>0)))
{
	return (playerone!=0)?playerone:playertwo;
}
else
return 0;
}

int getStrength(board_type * b)
{
int sum=0;
int weights[] = {0,1,10,50,600};
int i;
for( i=0;i<69;i++)
{
sum+=(getScore(b->consecutive_lines[i])>0)?weights[abs(getScore(b->consecutive_lines[i]))]:-weights[abs(getScore(b->consecutive_lines[i]))];
}
return sum+(b->current_player==PLAYER_ONE?16:-16);
}

int winnerIs(board_type * b)
{
int i;
for( i=0;i<69;i++)
{
if(getScore(b->consecutive_lines[i])==4)
{
return PLAYER_ONE;
}
else if(getScore(b->consecutive_lines[i])==-4)
{
return PLAYER_TWO;
}
}
return 0;

}

char * toString(board_type * b)
{



char * temp = (char *)malloc(b->rows*(b->cols+1)*sizeof(char)+1);

char * curr = temp;
int y;
int x;
 for( y=b->rows-1;y>-1;y--){

for( x=0;x<b->cols;x++)
{
if(getState(b->grid[x][y])==EMPTY)
*curr = '-';
else if(getState(b->grid[x][y])==PLAYER_ONE)
*curr = 'O';
else
*curr = 'X';
curr++;
}
*curr = '\n';
curr++;
}
return temp;
}

int get_current_player(board_type * b)
{
return b->current_player;
}

int getRandomPlayerMove(board_type *b)
{
int val =-1;
int possible[7];
int i;
for( i = 0; i <7; i++)
{
if(validMove(b,i))
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

 int minValue(board_type * cB, int ply);
 int maxValue(board_type * cB, int ply);
// should return a number
int getReasonedMove(board_type * cB)
{
int moves[7];
int highest = 0;
int i;
for( i=0;i<7;i++)
{
moves[i] = INT_MIN;
if(validMove(cB, i))
{
makeMove(cB,i);
moves[i] = minValue(cB,4);
if(moves[i]>=moves[highest])
highest=i;
undoMove(cB);
} 
}
return highest;
}

// don't change this unless you understand it
 int minValue(board_type * cB, int ply)
{
int moves[7];
int lowest = 0;
int i;
for( i=0;i<7;i++)
{
moves[i] = INT_MAX;
if(validMove(cB,i))
{
makeMove(cB,i);
if((winnerIs(cB) == 0) && ply>0)
{
moves[i] = maxValue(cB,ply-1);
}
else 
{

moves[i] = -getStrength(cB);


}
if(moves[i]<moves[lowest])
lowest=i;
undoMove(cB);
}

}

return moves[lowest];

}
//careful with this
int maxValue(board_type * cB, int ply)
{

int moves[7];
int highest = 0;
int i;
for( i=0;i<7;i++)
{
moves[i] = INT_MAX;
if(validMove(cB,i))
{
makeMove(cB,i);
if((winnerIs(cB) == 0) && ply>0)
{
moves[i] = minValue(cB,ply-1);
}
else 
moves[i] =-getStrength(cB);
if(moves[i]<moves[highest])
highest=i;
undoMove(cB);
}

}

return moves[highest];

}

/*
 * 
 */
int main(int argc, char** argv) {
 srand (time(NULL));
board_type * b = createBoard(7,6);

int input;
while((winnerIs(b)==0) && validMovesLeft(b))
 {
if(get_current_player(b) == PLAYER_ONE)	
{
scanf("%d", &input);
  makeMove(b,input);// Make it so!
}
 else
 makeMove(b, getReasonedMove(b));// Make it so!

printf("%s\n", toString(b));


}
 return 0;

}


