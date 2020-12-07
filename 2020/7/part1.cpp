// Advent of Code (2020) Day 7
// Forms a graph of each bag, where each directed edge indicates what bags
// contain a given bag.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Name of node to backtrack from
static const std::string wantedBag = "shiny gold";

// A node represents bag type, which are connected by edges indicating
// which bags contain other bag types
class Node {
	private:
		// An edge contains the node it points to and it's weight
		struct Edge {
        		Node * node;
        		size_t weight;
		};

		// Has this node been counted already?
		bool counted;

		// List of outgoing edges
		std::vector<Edge> edges;

		// Name of node
		std::string name_;

	public:
		Node(const std::string & name) {
			this->counted = false;
			this->name_ = name;
		}

		// Add a node as a neighbour (does nothing if already one)
		void addNeighbour(Node * neighbour, size_t amt) {
			// Check this node isn't already a neighbour
			Edge edge = {neighbour, amt};
			for (Edge & e : this->edges) {
				if (e.node->name() == edge.node->name()) {
					return;
				}
			}

			this->edges.push_back(edge);
		}

		// Count the number of connected neighbours (recursively)
		// In this context, it counts how many bags can contain this bag
		size_t countConnectedNodes() {
			// Mark counted
			this->counted = true;

			// Recursively count connected nodes
			size_t count = 0;
			for (Edge & e : this->edges) {
				if (!e.node->counted) {
					count++;
					count += e.node->countConnectedNodes();
				}
			}
			return count;
		}

		// Return this node's name
		std::string name() {
			return this->name_;
		}
};

// Returns an existing or new node for the given bag in the map
static Node * getNodeForBag(std::unordered_map<std::string, Node *> & map, const std::string & bag) {
	Node * node;
	if (map.count(bag) == 0) {
		node = new Node(bag);
		map[bag] = node;
	} else {
                node = map[bag];
	}
	return node;
}

int main(void) {
	// Map from bag type to it's node
	std::unordered_map<std::string, Node *> bags;

	// Read each line from input
	std::ifstream file("input.txt");
	std::string line;
	std::string tmp;

	// Iterate over each line
	Node * wanted = nullptr;
	while (std::getline(file, line)) {
		// Get the containing bag's type
		std::stringstream ss(line);
		std::string bag = "";
		ss >> bag >> tmp;
		bag += " " + tmp;

		// Get node
		Node * node = getNodeForBag(bags, bag);

		// Set as wanted if name matches
		if (bag == wantedBag) {
			wanted = node;
		}

		// Skip over 'bags contain'
		ss >> tmp >> tmp;

		// Get bags it contains
		int num;
		while (std::getline(ss, tmp, ' ')) {
			// Get number of bags contained
			ss >> num;
			if (ss.fail()) {
				break;
			}

			// Get bag type and skip over 'bag'/'bags'
			ss >> bag;
			ss >> tmp;
			bag += " " + tmp;
			ss >> tmp;

			// Get node for bag and assign as to other node
			Node * node2 = getNodeForBag(bags, bag);
			node2->addNeighbour(node, num);
		}
	}

	// Now backtrack from the bag we want, counting how many different
	// types we encounter
	if (wanted == nullptr) {
		std::cout << "Couldn't find the required bag in the input" << std::endl;

	} else {
		size_t count = wanted->countConnectedNodes();
		std::cout << count << " bags can contain the '" << wantedBag << "' bag" << std::endl;
	}

	// Free created nodes
	for (auto bag : bags) {
		delete bag.second;
	}
	return 0;
}
