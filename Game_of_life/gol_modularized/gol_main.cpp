#include "gol.h"

int main(void)
{
	int generations;
	std::cin >> generations;

	game_of_life game;
	init_game(game);

	print_cells(game);

	for (int iter = 0; iter < generations; iter++, init_new_round(game)) {
		evolve(game);
		print_cells(game, false, iter);
	}
	
	return 0;
}