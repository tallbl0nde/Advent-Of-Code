// Advent of Code (2020) Day 2
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Structure containing data for each line
struct Line {
	int pos1;
	int pos2;
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

		// <pos1>-<pos2>
		ss >> entry.pos1 >> tmp >> entry.pos2;

		// <char>:
		ss >> entry.chr >> tmp;

		// <password>
		ss >> entry.password;

		// Check if valid by checking each index
		// Note: Index starts at 1 :)
		size_t count = 0;
		if (entry.password[entry.pos1 - 1] == entry.chr) {
			count++;
		}
		if (entry.password[entry.pos2 - 1] == entry.chr) {
			count++;
		}
		if (count == 1) {
			valid++;
		}
	}

	std::cout << "Valid passwords: " << valid << std::endl;
	return 0;
}
