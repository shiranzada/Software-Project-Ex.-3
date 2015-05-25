#include "Draughts.h"
#include <limits.h>

int main()
{
	init_board(board);
	print_board(board);
	print_message(WRONG_MINIMAX_DEPTH);
	perror_message("TEST");
	return 0;
}


void print_line(){
	int i;
	printf("  |");
	for (i = 1; i < BOARD_SIZE*4; i++){
		printf("-");
	}
	printf("|\n");
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
	int i,j;
	print_line();
	for (j = BOARD_SIZE-1; j >= 0 ; j--)
	{
		printf((j < 9 ? " %d" : "%d"), j+1);
		for (i = 0; i < BOARD_SIZE; i++){
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		print_line();
	}
	printf("   ");
	for (j = 0; j < BOARD_SIZE; j++){
		printf(" %c  ", (char)('a' + j));
	}
	printf("\n");
}



void init_board(char board[BOARD_SIZE][BOARD_SIZE]){
	int i,j;
	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			if ((i + j) % 2 == 0){
				if (j <= 3){
					board[i][j] = WHITE_M;
				}
				else if (j >= 6){
					board[i][j] = BLACK_M;
				}
				else{
					board[i][j] = EMPTY;
				}
			}
			else{
				board[i][j] = EMPTY;
			}
		}
	}
}

int max(int depth, char player, board_t board, steps** bestStep){
	if (depth == 0){
		return score(board);
	}
	char otherPlayer = ('b' + 'w' - player);
	int currMin = INT_MAX;
	int stepScore;
	linkedList moves = setMoveList(otherPlayer, board);
	listNode* node = moves.first;
	while (node!=NULL)
	{
		stepScore = score(min(depth - 1, otherPlayer, moveDisc(*(steps*)node->data, player)));
		if (stepScore < currMin){
			currMin = stepScore;
			*bestStep = (steps*)node->data;
		}
	}
	return currMin;
}

int min(int depth, char player, board_t board, steps** bestStep){
	if (depth == 0){
		return score(board);
	}
	char otherPlayer = ('b' + 'w' - player);
	int currMin = INT_MIN;
	int stepScore;
	linkedList moves = setMoveList(otherPlayer, board);
	listNode* node = moves.first;
	while (node != NULL)
	{
		stepScore = score(max(depth - 1, otherPlayer, moveDisc(*(steps*)node->data, player)));
		if (stepScore > currMin){
			currMin = stepScore;
			*bestStep = (steps*)node->data;
		}
	}
	return currMin;
}

steps* minmax(char player){
	steps* bestStep = NULL;
	max(minmaxDepth, player, board, &bestStep)
}

