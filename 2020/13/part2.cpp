// Advent of Code (2020) Day 13
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

int main(void) {
	// Read in bus times with their 'slot'
	std::vector< std::pair<size_t, size_t> > buses;
	std::ifstream file("input.txt");
	std::string line;

	file >> line;
	file >> line;
	size_t i = 0;
	size_t slot = 0;
	while (i < line.length()) {
		// Check if 'x', and if so skip over
		if (line[i] == 'x') {
			i += 2;
			slot++;
			continue;
		}

		// Otherwise get number and proceed to next bus
		size_t amt = 0;
		size_t bus = std::stoi(line.substr(i), &amt);
		buses.push_back(std::make_pair(bus, slot));
		i += amt+1;
		slot++;
	}

	// Find when all buses depart at appropriate time, by:
	// 1) Finding the timestamp of the next 'new' bus that will depart
	//    when needed
	// 2) Storing this 'step' as how often we need to jump
	// 3) Repeating (1) for remaining buses
	size_t step = buses[0].first;
	size_t lastTimestamp = 0;
	size_t timestamp = 0;
	for (size_t nextBus = 1; nextBus < buses.size(); nextBus++) {
		// Find step for next bus to depart at right time
		bool departs = true;
		do {
			// Only run after first call (in case next bus also meets at same point)
			if (!departs) {
				timestamp += step;
			}
			departs = ((timestamp + buses[nextBus].second) % buses[nextBus].first) == 0;

		} while (!departs);

		// Determine the interval for all examined buses to meet the criteria
		step *= buses[nextBus].first;
	}

	// Print results
	std::cout << "The first timestamp is: " << timestamp << std::endl;
	return 0;
}
