#include <iostream>
#include <vector>

struct game_of_life {
	int grid_size;
	std::vector<std::vector<bool>> cells_A, cells_B;
	std::vector<std::vector<bool>> &old_state {cells_A};
	std::vector<std::vector<bool>> &new_state {cells_B};
};

void init_game(game_of_life &game);
void evolve(game_of_life &game);
void init_new_round(game_of_life &game);
void print_cells(const game_of_life &game, const bool print_old = true, const int iter = -1);