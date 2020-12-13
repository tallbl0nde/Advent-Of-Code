// Advent of Code (2020) Day 10
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(void) {
	// Gather all adapters into one vector
	int val;
	std::vector<int> adapters;
	std::ifstream file("input.txt");

	while (file >> val) {
		adapters.push_back(val);
	}

	// Sort from lowest to highest
	std::sort(adapters.begin(), adapters.end());

	// Add an 'adapter' for the device
	adapters.push_back(*(adapters.end()-1) + 3);

	// Iterate over, counting each number of differences
	size_t oneDiff = 0;
	size_t threeDiff = 0;
	int last = 0;
	for (const int a : adapters) {
		if (a - last == 1) {
			oneDiff++;
		} else if (a - last == 3) {
			threeDiff++;
		}

		last = a;
	}

	// Print result
	std::cout << "Your magic number: " << oneDiff * threeDiff << std::endl;
	return 0;
}
