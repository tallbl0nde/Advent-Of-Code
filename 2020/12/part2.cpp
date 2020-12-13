// Advent of Code (2020) Day 12
#include <fstream>
#include <iostream>
#include <string>

// Represents the 'ship', accept movements as described
// in the puzzle description
class Ship {
	private:
		// Current position
		int posX;
		int posY;

		// Waypoint position (relative to ship)
		int wayX;
		int wayY;

		// Rotate the waypoint using the given angle
		// Does so one step at a time, recursively
		void rotateWaypoint(int angle) {
			int tmp;

			// Negative angle
			if (angle < 0) {
				tmp = this->wayX;
				this->wayX = this->wayY;
				this->wayY = -tmp;

				this->rotateWaypoint(angle + 90);

			// Positive angle
			} else if (angle > 0) {
				tmp = this->wayX;
				this->wayX = -this->wayY;
				this->wayY = tmp;

				this->rotateWaypoint(angle - 90);
			}
		}

	public:
		// Constructor initializes initial position + waypoint
		Ship() {
			this->posX = 0;
			this->posY = 0;
			this->wayX = 10;
			this->wayY = -1;
		}

		// Processes the given movement
		void processMove(const std::string & move) {
			// Get 'argument'
			int val = std::stoi(move.substr(1));

			// Take action based on first character
			switch (move[0]) {
				case 'N':
					this->wayY -= val;
					break;

				case 'E':
					this->wayX += val;
					break;

				case 'S':
					this->wayY += val;
					break;

				case 'W':
					this->wayX -= val;
					break;

				case 'L':
					this->rotateWaypoint(-val);
					break;

				case 'R':
					this->rotateWaypoint(val);
					break;

				case 'F':
					this->posX += this->wayX * val;
					this->posY += this->wayY * val;
					break;
			}
		}

		// Return the ship's position as a pair <x, y>
		std::pair<int, int> position() {
			return std::make_pair(this->posX, this->posY);
		}
};

int main(void) {
	// Create ship object, and process moves line by line
	Ship ship;
	std::ifstream file("input.txt");
	std::string line;
	while (file >> line) {
		ship.processMove(line);
	}

	// Print final position
	std::pair<int, int> pos = ship.position();
	std::cout << "Manhattan distance: " << abs(pos.first) + abs(pos.second) << std::endl;
	return 0;
}
