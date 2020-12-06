// Advent of Code (2020) Day 6
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

// Adds the number of questions answered by everyone to the vector
static void countAllAndAppend(std::array<int, 26> & arr, const size_t exp, std::vector<int> & vec) {
        int amt = 0;
        for (const int count : arr) {
                amt += (count == exp ? 1 : 0);
        }

        if (amt > 0) {
        	vec.push_back(amt);
        }

	arr.fill(0);
}

int main(void) {
	// Read input file, collating each groups unique "yes" answers
	std::ifstream file("input.txt");
	std::vector<int> answered;

	// Iterate over each line, checking how many unique "yes" answers
	// there are per group
	std::string line;
	size_t people = 0;
	std::array<int, 26> answers;
	answers.fill(0);
	while (std::getline(file, line)) {
		// If a blank line, collate answers for group
		if (line.empty()) {
			countAllAndAppend(answers, people, answered);
			people = 0;

		// Otherwise mark answered questions
		} else {
			for (char c : line) {
				answers[c - 'a']++;
			}
			people++;
		}
	}

	// Check one more time to handle no blank line at the end
	countAllAndAppend(answers, people, answered);

	// Add together
	int final = 0;
	for (const int count : answered) {
		final += count;
	}

	// Print results
	std::cout << "Final sum: " << final << std::endl;
	return 0;
}
