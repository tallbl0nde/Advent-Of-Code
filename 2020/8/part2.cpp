// Advent of Code (2020): Day 8
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Enum of instruction types
enum class InstructionType {
	Acc,
	Jmp,
	Nop
};

// An instruction consists of the type, and the argument
struct Instruction {
	InstructionType type;
	int arg;
};

// Return an instruction from the given string
static Instruction stringToInstruction(const std::string & str) {
	Instruction i;
	std::stringstream ss(str);
	std::string tmp;

	// Get type
	ss >> tmp;
	if (tmp == "acc") {
		i.type = InstructionType::Acc;

	} else if (tmp == "jmp") {
		i.type = InstructionType::Jmp;

	} else {
		i.type = InstructionType::Nop;
	}

	// Get argument and convert to int
	ss >> i.arg;
	return i;
}

int main(void) {
	// 'Accumulator'
	int acc = 0;

	// Read in each line from the file, storing a bool alongside
	// which indicates if the instruction has been processed before
	//
	// This could be done better by instead keeping a list/pair of
	// executed line numbers
	std::ifstream file("input.txt");
	std::string tmp;
	std::vector< std::pair<Instruction, size_t> > lines;

	while (std::getline(file, tmp)) {
		Instruction i = stringToInstruction(tmp);
		lines.push_back(std::make_pair(i, 0));
	}

	// Change instructions using brute force and execute the (un)corrupted code
	// There is probably a more efficient way to do this, but given the complexity
	// of this problem it'll do :P
	for (size_t j = 0; j < lines.size(); j++) {
		// Check instruction
		Instruction & i = lines[j].first;
		if (i.type == InstructionType::Jmp) {
			i.type = InstructionType::Nop;

		} else if (i.type == InstructionType::Nop) {
			i.type = InstructionType::Jmp;

		// Otherwise continue as we know one is corrupted
		} else {
			continue;
		}

		// Now simulate as normal, stopping when an instruction is executed 100000 times
		// (assuming it's stuck if this happens)
		acc = 0;
		bool loop = false;
		size_t pc = 0;

		std::cout << "Swapping instruction " << j << std::endl;
		while (pc < lines.size()) {
			// Stop if in a loop
			if (lines[pc].second >= 100000) {
				loop = true;
				break;
			}

			// Increment execution count
			lines[pc].second++;

			// Execute instruction
			Instruction & i = lines[pc].first;
			switch (i.type) {
				case InstructionType::Acc:
					acc += i.arg;
					pc++;
					break;

				case InstructionType::Jmp:
					pc += i.arg;
					break;

				default:
					pc++;
					break;
			}
		}

		// Stop trying instructions if terminated normally
		if (!loop) {
			std::cout << "Terminated normally..." << std::endl;
			break;
		}

		// Otherwise reset execution counts
		acc = 0;
		for (auto & line : lines) {
			line.second = 0;
		}

		// And finally restore instruction
		if (i.type == InstructionType::Jmp) {
			i.type = InstructionType::Nop;
		} else {
			i.type = InstructionType::Jmp;
		}
	}

	// Print result
	std::cout << "Accumulator contains: " << acc << std::endl;
	return 0;
}
