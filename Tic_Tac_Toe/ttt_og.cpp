#include <iostream>
#include <cassert>

#define SIZE 3
#define N_PLAYERS 2
#define PLAYER_A 0
#define PLAYER_B 1

int main(void)
{
	// init board, 1 = x, 0 = o, -1 = blank
	int board[SIZE][SIZE];
	for (int row = 0; row < SIZE; row++) 
		for (int col = 0; col < SIZE; col++) 
			board[row][col] = -1;

	// each player's activity on each line (used to check for winning)	
	int rowSum[N_PLAYERS][SIZE];
	int colSum[N_PLAYERS][SIZE];
	int cross1[N_PLAYERS];
	int cross2[N_PLAYERS];
	for (int p = 0; p < N_PLAYERS; p++) {
		cross1[p] = cross2[p] = 0;
		for (int i = 0; i < SIZE; i++) 
			rowSum[p][i] = colSum[p][i] = 0;
	}

	// total steps
	int move {0};
	bool win {false};
	// whose turn
	int turn {PLAYER_A};

	// main body
	for (int i = 0; i < SIZE*SIZE; i++) {
		int row, col;
		bool input_ok;
		do {
			std::cout << "player " << turn << " turn: ";
			std::cin >> row >> col;
			input_ok = true;
			// check for invalid input
			if ( (row < 0 || row >= SIZE) || (col < 0 || col >= SIZE) ) {
				input_ok = false;
				std::cout << "invalid input" << std::endl;
			} else if (board[row][col] != -1) {
				input_ok = false;
				std::cout << "taken" << std::endl;
			}
		} while (input_ok == false);

		// logging
		board[row][col] = turn;
		rowSum[turn][row]++;
		colSum[turn][col]++;
		if (row == col) 
			cross1[turn]++;
		if (row + col == SIZE-1) 
			cross2[turn]++;
		move++;

		// print the board
		std::cout << std::endl;
		for (int r = 0; r < SIZE; r++) 
			for (int c = 0; c < SIZE; c++) {
				switch (board[r][c]) {
					case -1:
						std::cout << "#";
						break;
					case 0:
						std::cout << "0";
						break;
					case 1:
						std::cout << "1";
						break;
				
					default:
						std::cerr << "something wrong with the board" << std::endl;
						return 1;
				}
				if (c < SIZE-1) 
					std::cout << " ";
				else 
					std::cout << std::endl;
			}
		std::cout << std::endl;

		// check for winning
		if (move >= 5) {
			for (int i = 0; i < SIZE; i++) 
				if (rowSum[turn][i] == SIZE || colSum[turn][i] == SIZE) 
					win = true;
			if (win != true && (cross1[turn] == SIZE || cross2[turn] == SIZE)) 
				win = true;
			if (win) 
				break;
		}

		turn = (turn == PLAYER_A)? PLAYER_B: PLAYER_A;
	}

	if (win) 
		std::cout << "player " << turn << " wins after " << move <<" moves." << std::endl;
	else 
		std::cout << "It is a tie." << std::endl;

	return 0;
}