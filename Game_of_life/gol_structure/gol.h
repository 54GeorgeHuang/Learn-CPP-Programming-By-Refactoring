#define MAXSIZE 100

struct game_of_life {
	bool cells_a[MAXSIZE][MAXSIZE];
	bool cells_b[MAXSIZE][MAXSIZE];
	int grid_size;
	bool (*old_state)[MAXSIZE][MAXSIZE];
	bool (*new_state)[MAXSIZE][MAXSIZE];
};
