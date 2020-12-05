// Advent of Code (2020) Day 5
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

// Define dimensions of overall seats
static constexpr int numCols = 8;
static constexpr int numRows = 128;

// Helper to perform integer division but round up
static inline int divideAndRoundUp(int n, int d) {
	float val = n/static_cast<float>(d);
	return ceil(val);
}

int main(void) {
	// Iterate over each line in file, finding the seat
	// and keeping the highest id
	std::ifstream file("input.txt");
	std::string line;
	int id = 0;

	while (std::getline(file, line)) {
		// Start with the whole area
		int minCol = 0;
		int maxCol = numCols-1;
		int minRow = 0;
		int maxRow = numRows-1;

		// Iterate over all characters, shrinking the area down
		// to a single seat
		for (size_t i = 0; i < line.length(); i++) {
			bool last = (i == line.length() - 1);
			switch (line[i]) {
				// Keep front half
				case 'F':
					maxRow = minRow + (maxRow - minRow)/2;
					break;

				// Keep back half
				case 'B':
					minRow += divideAndRoundUp(maxRow - minRow, 2);
					if (last) {
						maxRow = minRow;
					}
					break;

				// Keep left half
				case 'L':
					maxCol = minCol + (maxCol - minCol)/2;
					break;

				// Keep right half
				case 'R':
					minCol += divideAndRoundUp(maxCol - minCol, 2);
					if (last) {
						maxCol = minCol;
					}
					break;
			}
		}

		// Keep the highest ID
		int possible = (maxRow * 8) + maxCol;
		if (possible > id) {
			id = possible;
		}
	}

	// Print results
	std::cout << "Highest seat ID: " << id << std::endl;
	return 0;
}
