#include <iostream>
#include <cassert>
#include "gol.h"

void init_game(game_of_life &game)
{
	std::cin >> game.grid_size;
	assert(1 <= game.grid_size && game.grid_size <= MAXSIZE);
	game.old_state = &(game.cells_a);
	game.new_state = &(game.cells_b);
	for (int row = 0; row < game.grid_size; row++) {
		for (int col = 0; col < game.grid_size; col++) {
			int temp;
			std::cin >> temp;
			game.cells_a[row][col] = (temp == 1)? true: false;
		}
	}
}

int numbers_of_live_neighbors(const game_of_life &game, const int row, const int col)
{
	int live_neighbors {0};

	for (int row_distance = -1; row_distance <= 1; row_distance++) 
		for (int col_distance= -1; col_distance <= 1; col_distance++) 

			// if not points to current cell	
			if ( !(row_distance == 0 && col_distance == 0)) {
				int neighbor_row {row + row_distance};
				int neighbor_col {col + col_distance};

				// check for row&col validness
				auto &cells {*(game.old_state)};
				if ( (0 <= neighbor_row && neighbor_row < game.grid_size) && (0 <= neighbor_col && neighbor_col < game.grid_size)) 
					if ( cells[neighbor_row][neighbor_col]) 
						live_neighbors++;
			}

	return live_neighbors;
}

void evolve(game_of_life &game)
{
	// set each cell's state
	for (int row = 0; row < game.grid_size; row++) 
		for (int col = 0; col < game.grid_size; col++) {
			
			// compute the numbers of live neighbors of current cell
			int live_neighbors {numbers_of_live_neighbors(game, row, col)};

			auto &cells_old {*(game.old_state)};
			auto &cells_new {*(game.new_state)};
			if (cells_old[row][col])
				cells_new[row][col] = (live_neighbors == 2 || live_neighbors == 3)? true: false;
			else
				cells_new[row][col] = (live_neighbors == 3)? true: false;
		}
}

void new_round_init(game_of_life &game)
{
	auto temp {game.old_state};
	game.old_state = game.new_state;
	game.new_state = temp;
}

void print_cells(const game_of_life &game, const bool print_old = true, const int iter = -1)
{
	std::cout << "\nAfter " << iter+1 << " generations:" << std::endl;

	auto &cells = print_old? *(game.old_state): *(game.new_state);

	for (int row = 0; row < game.grid_size; row++) 
		for (int col = 0; col < game.grid_size; col++)
			if (col+1 == game.grid_size)
				std::cout << cells[row][col] << std::endl;
			else
				std::cout << cells[row][col] << " ";

	std::cout << std::endl;
}

int main(void)
{
	int generations;
	std::cin >> generations;
	assert(generations > 0);

	game_of_life game;
	init_game(game);

	print_cells(game);

	for (int iter = 0; iter < generations; iter++, new_round_init(game)) {
		evolve(game);
		print_cells(game, false, iter);
	}
	
	return 0;
}