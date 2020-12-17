// Advent of Code (2020) Day 16
#include <fstream>
#include <iostream>
#include <regex>
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

	// Get error rate
	int errorRate = 0;
	for (auto & ticket : otherTickets) {
		errorRate += checkTicket(ticket, rules);
	}
	std::cout << "Error rate: " << errorRate << std::endl;
	return 0;
}
