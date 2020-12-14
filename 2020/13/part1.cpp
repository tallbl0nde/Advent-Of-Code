// Advent of Code (2020) Day 13
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

int main(void) {
	// Read in initial timestamp and bus times
	std::vector<int> buses;
	int timestamp;

	std::ifstream file("input.txt");
	file >> timestamp;

	std::string line;
	file >> line;
	size_t i = 0;
	while (i < line.length()) {
		// Check if 'x', and if so skip over
		if (line[i] == 'x') {
			i += 2;
			continue;
		}

		// Otherwise get number and proceed to next bus
		size_t amt = 0;
		int bus = std::stoi(line.substr(i), &amt);
		buses.push_back(bus);
		i += amt+1;
	}

	// Iterate over each bus, keeping the bus that is closest to timestamp
	int bus = 0;
	int diff = std::numeric_limits<int>::max();
	for (const int b : buses) {
		int tmp = timestamp % b;
		tmp = b - tmp;
		if (tmp < diff) {
			bus = b;
			diff = tmp;
		}
	}

	// Print results
	std::cout << "The magic number is: " << bus * diff << " (bus: " << bus << ", diff: " << diff << ")" << std::endl;
	return 0;
}
