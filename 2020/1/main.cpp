// Advent of Code (2020) Day 1
// Simple brute-force approach
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(void) {
	// Read in all numbers from file
	std::ifstream file("numbers.txt");
	std::vector<int> lines;
	int tmp;
	while (file >> tmp) {
		lines.push_back(tmp);
	}

	// Iterate over each possible combination, printing when suitable
	// values are discovered
	// This could likely be sped up by sorting or checking either end?
	bool twoDone = false;
	bool threeDone = false;
	for (size_t i = 0; i < lines.size(); i++) {
		for (size_t j = 0; j < lines.size(); j++) {
			if (i == j) {
				continue;
			}

			if (!twoDone && lines[i] + lines[j] == 2020) {
				twoDone = true;
				std::cout << lines[i] << " * " << lines[j] << " = " << lines[i] * lines[j] << std::endl;
			}

			if (!threeDone) {
				for (size_t k = 0; k < lines.size(); k++) {
					if (i == k) {
						continue;
					}

					if (lines[i] + lines[j] + lines[k] == 2020) {
						threeDone = true;
						std::cout << lines[i] << " * " << lines[j] << " * " << lines[k] << " = " << lines[i] * lines[j] * lines[k] << std::endl;
					}
				}
			}

			// Stop once we have what we need
			if (twoDone && threeDone) {
				return 0;
			}
		}
	}

	std::cout << "No suitable numbers found." << std::endl;
	return -1;
}
