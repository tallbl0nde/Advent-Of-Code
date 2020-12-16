// Advent of Code (2020) Day 15
#include <fstream>
#include <iostream>
#include <unordered_map>

// Wanted turn
static constexpr int wantedTurn = 30000000;

int main(void) {
	std::unordered_map<int, int> lastTurn;
	std::unordered_map<int, int> olderTurn;
	int tmp;
	int turn = 1;
	int spoken;

	// Start by using the starting numbers
	std::ifstream file("input.txt");
	while (file >> tmp) {
		// Mark turn and 'speak'
		lastTurn[tmp] = turn;
		olderTurn[tmp] = turn;
		spoken = tmp;
		turn++;

		// Skip over comma
		char comma;
		file >> comma;
	}

	// Now use most recent number
	while (turn <= wantedTurn) {
		if (turn % 1000000 == 0) {
			std::cout << "Up to turn: " << turn << std::endl;
		}
		// Speak 0 if not spoken before
		spoken = (lastTurn.count(spoken) == 0 ? 0 : lastTurn[spoken] - olderTurn[spoken]);

		// Mark as turn spoken in
		if (lastTurn.count(spoken) == 0) {
			lastTurn[spoken] = turn;
		}
		olderTurn[spoken] = lastTurn[spoken];
		lastTurn[spoken] = turn;
		turn++;
	}

	// Print result
	std::cout << "On turn " << wantedTurn << ": " << spoken << std::endl;
	return 0;
}
