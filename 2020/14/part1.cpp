// Advent of Code (2020) Day 14
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Class representing the 'computer'
class Computer {
	private:
		// Actual memory
		std::vector<size_t> mem;

		// Current bitmask
		std::string bitmask;

	public:
		// Constructor initializes computer
		Computer() {
			// Memory position doesn't seem to exceed 65535
			this->mem.resize(65535, 0);
			this->bitmask = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
		}

		// Set the bitmask for future writes
		void setBitmask(const std::string & mask) {
			this->bitmask = mask;
		}

		// Write the given value to specified memory location, applying the set mask
		void writeValue(const size_t addr, const size_t value) {
			// Convert value to string of bits
			std::string bits = "";
			size_t mask = 0b1;
			for (size_t i = 0; i < 36; i++) {
				if ((mask & value) >= 1) {
					bits = "1" + bits;
				} else {
					bits = "0" + bits;
				}
				mask = mask << 1;
			}

			// Change the value by applying the bitmask
			for (size_t i = 0; i < bits.size(); i++) {
				if (this->bitmask[i] != 'X') {
					bits[i] = this->bitmask[i];
				}
			}

			// Now convert to a number and store
			size_t num = std::stoull(bits, nullptr, 2);
			mem[addr] = num;
		}

		// Returns the sum of all values in vector
		size_t calculateSum() {
			size_t sum = 0;

			for (const size_t val : this->mem) {
				sum += val;
			}

			return sum;
		}
};

int main(void) {
	// Create computer object
	Computer comp;

	// Iterate over each line in the file
	std::ifstream file("input.txt");
	std::string line;
	std::string tmp;

	while (std::getline(file, line)) {
		// Convert line to stringstream
		std::stringstream ss(line);

		// Get first token, which is either 'mask' of 'mem[xxx]'
		ss >> tmp;
		if (tmp == "mask") {
			// Set bitmask
			ss >> tmp;
			ss >> tmp;
			comp.setBitmask(tmp);

		} else {
			// Write value
			size_t addr = std::stoull(tmp.substr(4));
			ss >> tmp;
			ss >> tmp;
			size_t val = std::stoull(tmp);
			comp.writeValue(addr, val);
		}
	}

	// Print results
	std::cout << "Sum of all values: " << comp.calculateSum() << std::endl;
	return 0;
}
