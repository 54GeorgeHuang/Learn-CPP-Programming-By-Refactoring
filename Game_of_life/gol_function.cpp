#include <iostream>
#include <cassert>
#define MAXSIZE 100

void read_grid(bool grid[MAXSIZE][MAXSIZE], const int grid_size)
{
	for (int row = 0; row < grid_size; row++) 
		for (int col = 0; col < grid_size; col++) {
			int temp;

			std::cin >> temp;
			grid[row][col] = (temp == 1)? true: false;
		}
}

int numbers_of_live_neighbors(const bool grid[MAXSIZE][MAXSIZE], const int now_row, const int now_col, const int grid_size)
{
	int live_neighbors {0};

	for (int row_distance = -1; row_distance <= 1; row_distance++) 
		for (int col_distance= -1; col_distance <= 1; col_distance++) 

			// if not points to current grid	
			if ( !(row_distance == 0 && col_distance == 0)) {
				int neighbor_row = now_row + row_distance;
				int neighbor_col = now_col + col_distance;

				// check for row&col validness
				if ( (0 <= neighbor_row && neighbor_row < grid_size) && (0 <= neighbor_col && neighbor_col < grid_size)) 
					if (grid[neighbor_row][neighbor_col]) 
						live_neighbors++;
			}

	return live_neighbors;
}

void evolve(const bool old_state[MAXSIZE][MAXSIZE], bool new_state[MAXSIZE][MAXSIZE], const int grid_size)
{
	// set each grid's state
	for (int row = 0; row < grid_size; row++) 
		for (int col = 0; col < grid_size; col++) {
			
			// compute the numbers of live neighbors of current grid
			int live_neighbors = numbers_of_live_neighbors(old_state, row, col, grid_size);

			if (old_state[row][col])
				new_state[row][col] = (live_neighbors == 2 || live_neighbors == 3)? true: false;
			else
				new_state[row][col] = (live_neighbors == 3)? true: false;
		}
}

void print_grid(const bool grid[MAXSIZE][MAXSIZE], const int grid_size, const int iter = -1)
{
	std::cout << "\nAfter " << iter+1 << " generations:" << std::endl;

	for (int row = 0; row < grid_size; row++) 
		for (int col = 0; col < grid_size; col++)
			if (col+1 == grid_size)
				std::cout << grid[row][col] << std::endl;
			else
				std::cout << grid[row][col] << " ";

	std::cout << std::endl;
}

int main(void)
{
	int grid_size, generations;
	std::cin >> grid_size >> generations;
	assert(1 <= grid_size && grid_size <= MAXSIZE && generations > 0);

	int old_state {0}, new_state {1};
	// 2: 2 states
	bool grid[2][MAXSIZE][MAXSIZE];

	read_grid(grid[old_state], grid_size);
	print_grid(grid[old_state], grid_size);

	for (int iter = 0; iter < generations; iter++) {
		evolve(grid[old_state], grid[new_state], grid_size);
		print_grid(grid[new_state], grid_size, iter);

		// old_state + new_state = 1
		old_state = (old_state == 0)? 1: 0;
		new_state = 1 - old_state;
	}
	
	return 0;
}