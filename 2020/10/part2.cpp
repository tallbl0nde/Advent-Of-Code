// Advent of Code (2020) Day 10
#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

// Required joltage (from part 1)
// (Device joltage adapter isn't counted here)
static constexpr size_t requiredJoltage = 170;

// Stores number of permutations from a given point for the given value
static std::unordered_map<size_t, size_t> sumFrom;

// Recursively counts how many combinations of adapters form the required joltage
static size_t countPermutationsForJoltage(const std::vector<int> adapters, const size_t req, size_t idx = 0, size_t last = 0) {
	size_t perms = 0;

	// Stop if past the end
	if (idx >= adapters.size()) {
		return perms;
	}

	// Try all remaining adapters
	for (size_t i = idx; i < adapters.size(); i++) {
		// Check current adapter, stopping if too far
		if (adapters[i] > req || adapters[i] - last > 3) {
			break;

		} else if (adapters[i] == req) {
			perms++;
			break;
		}

		// Check if already calculated and use that
		if (sumFrom.count(adapters[i]) == 1) {
			perms += sumFrom[adapters[i]];

		// Otherwise calculate and store result
		} else {
			size_t tmp = countPermutationsForJoltage(adapters, req, i+1, adapters[i]);
			sumFrom[adapters[i]] = tmp;
			perms += tmp;
		}
	}

	// Return permutations
	return perms;
}


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

	// Print result
	std::cout << "There are: " << countPermutationsForJoltage(adapters, requiredJoltage) << " distinct combinations" << std::endl;
	return 0;
}
