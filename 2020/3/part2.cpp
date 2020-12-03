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

// Return number of trees encountered for given slope
static size_t traverseWithSlope(const std::vector< std::vector<bool> > & map, size_t xSlope, size_t ySlope) {
        size_t count = 0;
        size_t x = 0;

        for (size_t y = 0; y < map.size(); y += ySlope) {
                if (treeAtPos(map, x, y)) {
                        count++;
                }
                x += xSlope;
        }

	return count;
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

	// Right 1, down 1
	size_t c1 = traverseWithSlope(map, 1, 1);

	// Right 3, down 1
	size_t c2 = traverseWithSlope(map, 3, 1);

	// Right 5, down 1
	size_t c3 = traverseWithSlope(map, 5, 1);

	// Right 7, down 1
	size_t c4 = traverseWithSlope(map, 7, 1);

	// Right 1, down 2
	size_t c5 = traverseWithSlope(map, 1, 2);

	// Multiply and print
	size_t amt = c1 * c2 * c3 * c4 * c5;
	std::cout << "Final magic number: " << amt << std::endl;

	return 0;
}
