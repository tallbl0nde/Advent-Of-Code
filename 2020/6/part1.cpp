// Advent of Code (2020) Day 6
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

// Adds the number of true's in the array to the vector
static void countYesAndAppend(std::array<bool, 26> & arr, std::vector<int> & vec) {
        int amt = 0;
        for (const bool yes : arr) {
                amt += (yes ? 1 : 0);
        }

        if (amt > 0) {
        	vec.push_back(amt);
        }

	arr.fill(false);
}

int main(void) {
	// Read input file, collating each groups unique "yes" answers
	std::ifstream file("input.txt");
	std::vector<int> answered;

	// Iterate over each line, checking how many unique "yes" answers
	// there are per group
	std::string line;
	std::array<bool, 26> answers;
	answers.fill(false);
	while (std::getline(file, line)) {
		// If a blank line, collate answers for group
		if (line.empty()) {
			countYesAndAppend(answers, answered);

		// Otherwise mark answered questions
		} else {
			for (char c : line) {
				answers[c - 'a'] = true;
			}
		}
	}

	// Check one more time to handle no blank line at the end
	countYesAndAppend(answers, answered);

	// Add together
	int final = 0;
	for (const int count : answered) {
		final += count;
	}

	// Print results
	std::cout << "Final sum: " << final << std::endl;
	return 0;
}
