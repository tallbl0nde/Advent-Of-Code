// Advent of Code (2020) Day 14
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

// Class representing the 'computer'
class Computer {
	private:
		// Actual memory
		std::map<size_t, size_t> mem;

		// Current bitmask
		std::string bitmask;

		// Recursively enumerates addresses from the given string and writes value
		void recursiveAddrWrite(std::string bits, const size_t value) {
			// Recursively call with next 'X' being both 0 and 1
			bool completeAddr = true;
			for (char & c : bits) {
				if (c == 'X') {
					c = '0';
					recursiveAddrWrite(bits, value);
					c = '1';
					recursiveAddrWrite(bits, value);
					completeAddr = false;
					break;
				}
			}

			// Convert to a number and store if a full address
			if (completeAddr) {
				size_t num = std::stoull(bits, nullptr, 2);
				this->mem[num] = value;
			}
		}

	public:
		// Constructor initializes computer
		Computer() {
			this->bitmask = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
		}

		// Set the bitmask for future writes
		void setBitmask(const std::string & mask) {
			this->bitmask = mask;
		}

		// Write the given value to specified memory location, applying the set mask
		void writeValue(const size_t addr, const size_t value) {
			// Convert addr to string of bits
			std::string bits = "";
			size_t mask = 0b1;
			for (size_t i = 0; i < 36; i++) {
				if ((mask & addr) >= 1) {
					bits = "1" + bits;
				} else {
					bits = "0" + bits;
				}
				mask = mask << 1;
			}

			// Change the address by applying the bitmask
			for (size_t i = 0; i < bits.size(); i++) {
				switch (this->bitmask[i]) {
					case '0':
						break;

					case '1':
					case 'X':
						bits[i] = this->bitmask[i];
						break;
				}
			}

			// Write to all possible addresses
			this->recursiveAddrWrite(bits, value);
		}

		// Returns the sum of all values in vector
		size_t calculateSum() {
			size_t sum = 0;

			for (const std::pair<size_t, size_t> val : this->mem) {
				sum += val.second;
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
