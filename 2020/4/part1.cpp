// Advent of Code (2020) Day 4
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Enum for each field in a passport
// Used to index element in array
enum class Field {
	byr,
	iyr,
	eyr,
	hgt,
	hcl,
	ecl,
	pid,
	cid
};
Field stringToField(const std::string & str) {
	if (str == "byr") {
		return Field::byr;

	} else if (str == "iyr") {
		return Field::iyr;

	} else if (str == "eyr") {
		return Field::eyr;

	} else if (str == "hgt") {
		return Field::hgt;

	} else if (str == "hcl") {
		return Field::hcl;

	} else if (str == "ecl") {
		return Field::ecl;

	} else if (str == "pid") {
		return Field::pid;

	} else {
		return Field::cid;
	}
}

// Return whether all elements are true
static inline bool allTrue(const std::vector<bool> & vec) {
	for (const bool & elm : vec) {
		if (!elm) {
			return false;
		}
	}
	return true;
}

// Return the field keyword from a string
static std::string getField(std::string str) {
	std::stringstream ss(str);
	std::getline(ss, str, ':');
	return str;
}

// Reset bool vector to all false
static inline void setFalse(std::vector<bool> & vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		vec[i] = false;
	}
}

int main(void) {
	// Read input from file
	std::ifstream file("input.txt");
	std::string line;
	std::string tmp;
	size_t count = 0;

	// Array of whether fields are present
	std::vector<bool> fieldPresent(7);
	setFalse(fieldPresent);

	while (std::getline(file, line)) {
		// Iterate over each token, checking field
		if (!line.empty()) {
			std::stringstream ss(line);
			while (std::getline(ss, tmp, ' ')) {
				std::string field = getField(tmp);
				Field f = stringToField(field);
				if (f != Field::cid) {
					fieldPresent[static_cast<int>(f)] = true;
				}
			}

		// If line is blank (newline), check if valid and reset
		} else {
			if (allTrue(fieldPresent)) {
				count++;
			}
			setFalse(fieldPresent);
		}
	}

	// Check again (handle no empty line at end)
	if (allTrue(fieldPresent)) {
		count++;
	}

	// Print results
	std::cout << "Valid passports: " << count << std::endl;
	return 0;
}
