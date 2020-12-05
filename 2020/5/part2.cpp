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
	// We have an array of 952 elements as 952 was the highest id (from part 1)
	// An element is true if the seat is taken
	bool seatTaken[952];
	for (size_t i = 0; i < 951; i++) {
		seatTaken[i] = false;
	}

	// Iterate over each line in file, marking whether each seat is present
	std::ifstream file("input.txt");
	std::string line;

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

		// Mark seat as occupied
		int id = (maxRow * 8) + maxCol;
		seatTaken[id] = true;
	}

	// Iterate from back to front, finding our seat
	// We start 950 as we can't look right of 951, plus we know it's occupied
	int id = -1;
	for (int i = 950; i >= 0; i--) {
		// Skip occupied seats
		if (seatTaken[i]) {
			continue;
		}

		if (seatTaken[i-1] && seatTaken[i+1]) {
			id = i;
			break;
		}
	}

	// Print seat
	std::cout << "Your seat is: " << id << std::endl;
	return 0;
}
