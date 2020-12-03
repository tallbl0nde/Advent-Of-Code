// Advent of Code (2020) Day 3
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Return whether cell at (x, y) contains a tree
// Handles wrapping around
static inline bool treeAtPos(const std::vector< std::vector<bool> > & map, size_t x, size_t y) {
	x = x % map[0].size();
	return map[y][x];
}

int main(void) {
	// Read in lines and form map (2d vector)
	std::ifstream file("input.txt");
	std::string tmp;
	std::vector< std::vector<bool> > map;

	while (std::getline(file, tmp)) {
		// Iterate over each character, pushing a new row into the vector
		std::vector<bool> row;
		for (char & c : tmp) {
			// Mark true if cell contains a tree
			row.push_back(c == '#');
		}
		map.push_back(row);
	}

	// Now check how many trees we encounter
	size_t count = 0;
	size_t x = 0;
	for (size_t y = 0; y < map.size(); y++) {
		if (treeAtPos(map, x, y)) {
			count++;
		}
		x += 3;
	}

	std::cout << "Encountered " << count << " trees" << std::endl;

	return 0;
}
