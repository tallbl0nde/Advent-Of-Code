// Advent of Code (2020) Day 16
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>

// Rules for a field
struct Rule {
	int min1;
	int max1;
	int min2;
	int max2;
};

// Returns whether the passed ticket is valid or not
// 0: valid, non-zero: invalid
static int checkTicket(const std::vector<int> & ticket, const std::vector<Rule> & rules) {
	int errorRate = 0;
	for (const int field : ticket) {
		bool followsRule = false;
		for (const Rule rule : rules) {
			if ((field >= rule.min1 && field <= rule.max1) || (field >= rule.min2 && field <= rule.max2)) {
				followsRule = true;
				break;
			}
		}

		if (!followsRule) {
			errorRate += field;
		}
	}
	return errorRate;
}

int main(void) {
	std::ifstream file("input.txt");
	std::string line;
	size_t tmp;

	// Read 'rules' first
	std::vector<Rule> rules;
	std::smatch matches;
	std::regex regex("(?:(?![0-9]).)*([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)");
	while (std::getline(file, line) && !line.empty()) {
		Rule rule;
		if (std::regex_match(line, matches, regex)) {
			rule.min1 = std::stoi(matches[1].str());
			rule.max1 = std::stoi(matches[2].str());
			rule.min2 = std::stoi(matches[3].str());
			rule.max2 = std::stoi(matches[4].str());
			rules.push_back(rule);
		}
	}

	// Now read our ticket
	std::getline(file, line);
	std::getline(file, line);
	std::vector<int> ourTicket;
	tmp = 0;
	size_t amt = 0;
	while (tmp < line.length()) {
		ourTicket.push_back(std::stoi(line.substr(tmp), &amt));
		tmp += amt+1;
	}


	// And process everyone elses
	std::getline(file, line);
	std::getline(file, line);
	std::vector< std::vector<int> > otherTickets;
	while (std::getline(file, line)) {
		tmp = 0;
		std::vector<int> ticket;
		while (tmp < line.length()) {
			ticket.push_back(std::stoi(line.substr(tmp), &amt));
			tmp += amt+1;
		}
		otherTickets.push_back(ticket);
	}

	// Remove any invalid tickets
	tmp = 0;
	while (tmp < otherTickets.size()) {
		if (checkTicket(otherTickets[tmp], rules) != 0) {
			otherTickets.erase(otherTickets.begin() + tmp);
		} else {
			tmp++;
		}
	}

	// Final map from rule index to field index
	std::vector<int> map;
	map.resize(rules.size());

	// Iterate over each column for each ticket, marking if the column fits a rule
	// column<rule>
	std::vector< std::vector<bool> > fitsVec;
	fitsVec.resize(rules.size());
	for (size_t c = 0; c < fitsVec.size(); c++) {
		fitsVec[c].resize(rules.size(), false);

		// Iterate over all rules to check it matches
		for (size_t r = 0; r < rules.size(); r++) {
			// Iterate over each ticket's column
			bool allFit = true;
			for (const auto & ticket : otherTickets) {
				int field = ticket[c];
				Rule rule = rules[r];
				bool fits = (field >= rule.min1 && field <= rule.max1) || (field >= rule.min2 && field <= rule.max2);
				if (!fits) {
					allFit = false;
					break;
				}
			}

			// Mark as potential rule for column
			fitsVec[c][r] = allFit;
		}
	}

	// Now derive all fields
	size_t done = 0;
	while (done < map.size()) {
		// Find column that only has one possible rule
		for (size_t col = 0; col < fitsVec.size(); col++) {
			size_t matching = 0;
			size_t index = 0;
			for (size_t row = 0; row < fitsVec[col].size(); row++) {
				if (fitsVec[col][row]) {
					index = row;
					matching++;
				}
			}

			// If only one matching rule, add to map and remove as candidate for other columns
			if (matching == 1) {
				map[index] = col;
				for (size_t col2 = 0; col2 < fitsVec.size(); col2++) {
					fitsVec[col2][index] = false;
				}
				break;
			}
		}

		done++;
	}

	// Print result
	tmp = 1;
	for (size_t i = 0; i < 6; i++) {
		tmp *= static_cast<size_t>(ourTicket[map[i]]);
	}
	std::cout << "Your magic number: " << tmp << std::endl;
	return 0;
}
