// Advent of Code (2020) Day 2
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Structure containing data for each line
struct Line {
	int min;
	int max;
	char chr;
	std::string password;
};

int main(void) {
	// Prepare file
	std::ifstream file("input.txt");
	std::string line;
	size_t valid = 0;
	char tmp;

	// Iterate over each line
	while (std::getline(file, line)) {
		// Convert line to stringstream and extract data
		Line entry;
		std::stringstream ss(line);

		// <min>-<max>
		ss >> entry.min >> tmp >> entry.max;

		// <char>:
		ss >> entry.chr >> tmp;

		// <password>
		ss >> entry.password;

		// Check if valid by iterating over, counting characters
		size_t count = 0;
		for (char & c : entry.password) {
			if (c == entry.chr) {
				count++;
			}
		}

		if (count >= entry.min && count <= entry.max) {
			valid++;
		}
	}

	std::cout << "Valid passwords: " << valid << std::endl;
	return 0;
}
