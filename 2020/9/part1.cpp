// Advent of Code (2020): Day 9
#include <fstream>
#include <iostream>
#include <vector>

int main(void) {
	// Vector to store last 25 numbers
	std::vector<size_t> recent;

	// Iterate over each line, checking that the current number
	// is the sum of any two previous 25 numbers
	// This breaks out when the number isn't the sum of 2 numbers
	std::ifstream file("input.txt");
	size_t num;
	while (file >> num) {
		// Edge case: we don't have 25 numbers yet
		if (recent.size() < 25) {
			recent.push_back(num);
			continue;
		}

		// Otherwise check if number is sum of 2 others
		bool havePair = false;
		for (size_t i = 0; i < recent.size()-1; i++) {
			for (size_t j = i+1; j < recent.size(); j++) {
				// Must be different values
				if (recent[i] == recent[j]) {
					continue;
				}

				if (recent[i] + recent[j] == num) {
					havePair = true;
					break;
				}
			}
		}

		// If there's no pair then print out the number and exit
		if (!havePair) {
			std::cout << "The first invalid number is: " << num << std::endl;
			return 0;
		}

		// Otherwise cycle numbers around
		recent.erase(recent.begin());
		recent.push_back(num);
	}

	std::cout << "All numbers were as expected" << std::endl;
	return 0;
}
