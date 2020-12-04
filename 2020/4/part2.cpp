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

// Returns whether field is valid or not
static bool checkField(const std::string & str) {
	// Split into two tokens
	std::string field;
	std::string value;
	std::stringstream ss(str);
	std::getline(ss, field, ':');
	std::getline(ss, value, ':');

	// Check based on field
	Field f = stringToField(field);
	int val;
	switch (f) {
		case Field::byr:
			val = std::stoi(value);
			return (val >= 1920 && val <= 2002);

		case Field::iyr:
			val = std::stoi(value);
			return (val >= 2010 && val <= 2020);

		case Field::eyr:
			val = std::stoi(value);
			return (val >= 2020 && val <= 2030);

		case Field::hgt: {
			bool cm = (value[value.length() - 2] == 'c' && value[value.length() - 1] == 'm');
			bool in = (value[value.length() - 2] == 'i' && value[value.length() - 1] == 'n');
			val = std::stoi(value);
			if (cm) {
				return (val >= 150 && val <= 193);
			} else if (in) {
				return (val >= 59 && val <= 76);
			}
			return false;
		}

		case Field::hcl: {
			bool ok = (value[0] == '#' && value.length() == 7);
			if (ok) {
				for (size_t i = 1; i < value.length(); i++) {
					if (!((value[i] >= '0' && value[i] <= '9') || (value[i] >= 'a' && value[i] <= 'f'))) {
						ok = false;
						break;
					}
				}
			}
			return ok;
		}

		case Field::ecl:
			return (value == "amb" || value == "blu" || value == "brn" || value == "gry" || value == "grn" || value == "hzl" || value == "oth");

		case Field::pid: {
			bool ok = (value.length() == 9);
			if (ok) {
				for (char c : value) {
					if (!(c >= '0' && c <= '9')) {
						ok = false;
						break;
					}
				}
			}
			return ok;
		}
	}

	return false;
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
				bool valid = checkField(tmp);
				if (valid) {
					std::stringstream ss2(tmp);
	                                std::getline(ss2, tmp, ':');
	                                Field f = stringToField(tmp);
        	                        if (f != Field::cid) {
                	                        fieldPresent[static_cast<int>(f)] = true;
                        	        }
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
