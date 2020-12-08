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
	std::vector< std::pair<Instruction, bool> > lines;

	while (std::getline(file, tmp)) {
		Instruction i = stringToInstruction(tmp);
		lines.push_back(std::make_pair(i, false));
	}

	// Now execute the instructions until we reencounter an instruction,
	// 'breaking' and printing the accumulator's value
	size_t pc = 0;
	while (pc < lines.size()) {
		// Check if already executed
		if (lines[pc].second) {
			break;
		}

		// Mark as executed
		lines[pc].second = true;

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

	// Print result
	std::cout << "Accumulator contains: " << acc << std::endl;
	return 0;
}
