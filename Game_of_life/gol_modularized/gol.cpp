#include "gol.h"

void init_game(game_of_life &game)
{
	std::cin >> game.grid_size;
	game.cells_B = game.cells_A = std::vector<std::vector<bool>> (game.grid_size, std::vector<bool>(game.grid_size));
	for (auto &row : game.cells_A)
		for (auto cell = row.begin(); cell < row.end(); cell++) {
			int temp;
			std::cin >> temp;
			*cell = (temp == 1)? true: false;
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
				if ( (0 <= neighbor_row && neighbor_row < game.grid_size) && (0 <= neighbor_col && neighbor_col < game.grid_size)) 
					if (game.old_state[neighbor_row][neighbor_col]) 
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

			if (game.old_state[row][col])
				game.new_state[row][col] = (live_neighbors == 2 || live_neighbors == 3)? true: false;
			else
				game.new_state[row][col] = (live_neighbors == 3)? true: false;
		}
}

void init_new_round(game_of_life &game)
{
	auto temp {game.old_state};
	game.old_state = game.new_state;
	game.new_state = temp;
}

void print_cells(const game_of_life &game, const bool print_old, const int iter)
{
	std::cout << "\nAfter " << iter+1 << " generations:" << std::endl;

	auto &cells = print_old? game.old_state: game.new_state;

	for (int row = 0; row < game.grid_size; row++) 
		for (int col = 0; col < game.grid_size; col++)
			if (col+1 == game.grid_size)
				std::cout << cells[row][col] << std::endl;
			else
				std::cout << cells[row][col] << " ";

	std::cout << std::endl;
}