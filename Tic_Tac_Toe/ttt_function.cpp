#include <iostream>
#include <cassert>
#include <cstdlib>

#define SIZE 3
#define N_PLAYERS 2
#define PLAYER_A 0
#define PLAYER_B 1

inline void init(int board[SIZE][SIZE], int rowSum[N_PLAYERS][SIZE], int colSum[N_PLAYERS][SIZE], int cross1_sum[N_PLAYERS], int cross2_sum[N_PLAYERS])
{
	for (int row = 0; row < SIZE; row++) 
		for (int col = 0; col < SIZE; col++) 
			board[row][col] = -1;
	for (int p = 0; p < N_PLAYERS; p++) {
		cross1_sum[p] = cross2_sum[p] = 0;
		for (int i = 0; i < SIZE; i++) 
			rowSum[p][i] = colSum[p][i] = 0;
	}
}

inline int whose_turn(const int move) 
{
	return (move % N_PLAYERS == PLAYER_A)? PLAYER_A: PLAYER_B;
}

inline int who_moved(const int move) 
{
	return (whose_turn(move) == PLAYER_A)? PLAYER_B: PLAYER_A;
}

inline void play(int board[SIZE][SIZE], const int move, const int row, const int col, int rowSum[N_PLAYERS][SIZE], int colSum[N_PLAYERS][SIZE], int cross1_sum[N_PLAYERS], int cross2_sum[N_PLAYERS])
{
	int turn {whose_turn(move)};

	board[row][col] = turn;
	rowSum[turn][row]++;
	colSum[turn][col]++;
	if (row == col) 
		cross1_sum[turn]++;
	if (row + col == SIZE-1) 
		cross2_sum[turn]++;
}

inline bool check_row_col(const int move, const int sum[N_PLAYERS][SIZE])
{
	int turn = who_moved(move);
	for (int i= 0; i < SIZE; i++) 
		if (sum[turn][i] == SIZE)
			return true;

	return false;
}

inline bool check_diag(const int move, const int cross1_sum[N_PLAYERS], const int cross2_sum[N_PLAYERS])
{
	int turn = who_moved(move);
	return (cross1_sum[turn] == SIZE || cross2_sum[turn] == SIZE)? true: false;
}

inline bool check_win(const int move, const int rowSum[N_PLAYERS][SIZE], const int colSum[N_PLAYERS][SIZE], const int cross1_sum[N_PLAYERS], const int cross2_sum[N_PLAYERS])
{
	return (check_row_col(move, rowSum) || check_row_col(move, colSum) || check_diag(move, cross1_sum, cross2_sum))? true: false;
}

inline bool my_input(const int move, int& row, int& col, const int board[SIZE][SIZE])
{
	if (whose_turn(move) == PLAYER_A)
		std::cout << "player o turn: ";
	else
		std::cout << "player x turn: ";
	if ( !(std::cin >> row >> col)) {
		std::cerr << "stop fucking with me" << std::endl;
		exit(1);
	}
	
	if ( (row < 0 || row >= SIZE) || (col < 0 || col >= SIZE) ) {
		std::cout << "invalid input" << std::endl;
		return false;
	} else if (board[row][col] != -1) {
		std::cout << "taken" << std::endl;
		return false;
	} else 
		return true;
}

inline void print_board(const int board[SIZE][SIZE])
{
	std::cout << "\n" <<std::endl;
	for (int row = 0; row < SIZE; row++) 
		for (int col = 0; col < SIZE; col++) {
			switch (board[row][col]) {
				case -1:
					std::cout << "!";
					break;
				case 0:
					std::cout << "o";
					break;
				case 1:
					std::cout << "x";
					break;
			
				default:
					std::cerr << "something wrong with the board" << std::endl;
					exit(2);
			}
			if (col < SIZE-1) 
				std::cout << " ";
			else 
				std::cout << std::endl;
		}
	std::cout << std::endl;
}

int main(void)
{
	// board, 1 = x, 0 = o, -1 = !(blank)
	int board[SIZE][SIZE];

	// each player's activity on each line (used to check for winning)	
	int rowSum[N_PLAYERS][SIZE];
	int colSum[N_PLAYERS][SIZE];
	int cross1_sum[N_PLAYERS];
	int cross2_sum[N_PLAYERS];

	init(board, rowSum, colSum, cross1_sum, cross2_sum);

	// total steps
	int move {0};

	// main body
	bool win {false};
	for (int i = 0; i < SIZE*SIZE && win == false; i++) {
		print_board(board);
		int row, col;
		while (my_input(move, row, col, board) == false);

		play(board, move, row, col, rowSum, colSum, cross1_sum, cross2_sum);
		move++;

		win = check_win(move, rowSum, colSum, cross1_sum, cross2_sum);
	}

	print_board(board);
	if (win) 
		if (who_moved(move) == PLAYER_A)
			std::cout << "player o wins after " << move <<" moves." << std::endl;
		else
			std::cout << "player x wins after " << move <<" moves." << std::endl;
	else 
		std::cout << "It is a tie." << std::endl;

	return 0;
}