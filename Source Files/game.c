
int equalsPosition(point_type *a, point_type *b)
{
	return ((a->x == b->x) && (a->y == b->y));
}


void setState(point_type *a, int player)
{
	a->state = player;
}


int getState(point_type *a)
{
	return (a->state);
}


int validMove(board_type *board, int column)
{
	return board->heights[column] < board->rows;
}


void makeMove(board_type *board, int column)
{
	setState(board->grid[column][board->heights[column]], board->current_player);
	board->heights[column]++;
	board->moves_made++;
	board->moves[b->moves_made] = column;
	board->current_player = -board->current_player;
}


void undoMove(board_type *board)
{
	setState(board->grid[board->moves[board->moves_made]][board->heights[board->moves[board->moves_made]]-1],(EMPTY));
	board->heights[board->moves[board->moves_made]]--;
	board->moves_made--;
	board->current_player = -board->current_player;
}


int validMovesLeft(board_type *board)
{
	return board->moves_made < ((board->cols * board->rows)-1);
}


int getScore(point_type *points[]) 
{
	int playerone=0;
	int playertwo=0;
	int i;

	for(i = 0; i < 4; i++)
	{
		if(getState(points[i]) == PLAYER_ONE)
		playerone++;

		else if(getState(points[i]) == PLAYER_TWO)
		playertwo++;
	}

	if((playerone + playertwo > 0) && (!(playerone > 0 && playertwo > 0)))
	{
		return (playerone! = 0) ? playerone : playertwo ;
	}

	else
	return 0;
}


int getStrength(board_type *board)
{
	int sum = 0;
	int weights[] = {0,1,10,50,600};
	int i;

	for( i=0;i<69;i++)
	{
		sum += (getScore(board->consecutive_lines[i])>0) ? \
		weights[abs(getScore(board->consecutive_lines[i]))]:-weights[abs(getScore(board->consecutive_lines[i]))];
	}

	return sum + (board->current_player == PLAYER_ONE ? 16 : -16);
}


int winnerIs(board_type *board)
{
	int i;
	for(i = 0; i<69; i++)
	{
		if(getScore(board->consecutive_lines[i]) == 4)
		{
		return PLAYER_ONE;
		}
		else if(getScore(board->consecutive_lines[i]) == -4)
		{
		return PLAYER_TWO;
		}
	}

	return 0;

}


int getCurrentPlayer(board_type *board)
{
return board->current_player;
}


