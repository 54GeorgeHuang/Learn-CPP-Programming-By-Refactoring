#include <iostream>
#include <cassert>

int main(void)
{
	int grid_size, generations;
	std::cin >> grid_size >> generations;
	assert(grid_size >= 1 && generations >= 0);

	int old_state {0}, new_state {1};
	// 2: 2 states
	bool grid[2][grid_size][grid_size];
	
	for (int row = 0; row < grid_size; row++) 
		for (int col = 0; col < grid_size; col++) {
			int temp;
			std::cin >> temp;
			grid[old_state][row][col] = (temp == 1)? true: false;
		}
	

	for (int iter = 0; iter < generations; iter++) {
		// set each grid's state
		for (int now_row = 0; now_row < grid_size; now_row++) 
			for (int now_col = 0; now_col < grid_size; now_col++) {

				int live_neighbors = 0;

				// compute numbers of live neighbors
				for (int row_distance = -1; row_distance <= 1; row_distance++) 
					for (int col_distance = -1; col_distance <= 1; col_distance++) 
						// if not points to self
						if ( !(row_distance == 0 && col_distance == 0)) {
							int neighbor_row = now_row + row_distance;
							int neighbor_col = now_col + col_distance;
							// check for row&col validness
							if ( (neighbor_row >= 0 && neighbor_row < grid_size) && (neighbor_col >= 0 && neighbor_col < grid_size )) 
								if (grid[old_state][neighbor_row][neighbor_col]) 
									live_neighbors++;
						}

				// compute now_cell new state
				if (grid[old_state][now_row][now_col]) 
					grid[new_state][now_row][now_col] = (live_neighbors == 2 || live_neighbors == 3)? true: false;
				else 
					grid[new_state][now_row][now_col] = (live_neighbors == 3)? true: false;
			}
		

		// print the grid
		std::cout << "\nAfter " << iter+1 << " generations:" << std::endl;
		for (int row = 0; row < grid_size; row++) {
			for (int col = 0; col < grid_size; col++) {
				if (col+1 == grid_size) {
					std::cout << grid[new_state][row][col] << std::endl;
				} else {
					std::cout << grid[new_state][row][col] << " ";
				}
			}
		}
		std::cout << std::endl;

		old_state = (old_state == 1)? 0: 1;
		new_state = (new_state == 1)? 0: 1;
	}

	return 0;
}