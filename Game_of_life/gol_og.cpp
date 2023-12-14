#include <iostream>
#include <cassert>

int main(void)
{
	int n, k;
	std::cin >> n >> k;
	assert(n >= 1 && k >= 0);

	int from {0}, to {1};
	bool life[2][n][n];
	
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			int temp;
			std::cin >> temp;
			life[from][row][col] = (temp == 1)? true: false;
		}
	}

	for (int iter = 0; iter < k; iter++) {
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {

				int neighbor = 0;
				for (int drow = -1; drow <= 1; drow++) {
					for (int dcol = -1; dcol <= 1; dcol++) {
						if (!(drow == 0 && dcol == 0)) {
							int nRow = row + drow;
							int nCol = col + dcol;
							if ((nRow >= 0 && nRow < n) && (nCol >= 0 && nCol < n) && life[from][nRow][nCol]) {
								neighbor++;
							}
						}
					}
				}

				if (life[from][row][col]) {
					life[to][row][col] = (neighbor == 2 || neighbor == 3)? true: false;
				} else {
					life[to][row][col] = (neighbor == 3)? true: false;
				}
			}
		}

		from = (from == 1)? false: true;
		to = (to == 1)? false: true;
	}

	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (col == n-1) {
				std::cout << life[from][row][col] << std::endl;
			} else {
				std::cout << life[from][row][col] << " ";
			}
		}
	}

	return 0;
}