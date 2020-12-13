// Advent of Code (2020) Day 12
#include <fstream>
#include <iostream>
#include <string>

// Represents the 'ship', accept movements as described
// in the puzzle description
class Ship {
	private:
		// Enumeration of possible directions
		enum class Direction {
			North = 0,
			East  = 1,
			South = 2,
			West  = 3
		};

		// Current position
		int posX;
		int posY;

		// Current direction
		Direction dir;

		// Rotate the ship's direction using the given angle
		void rotate(int angle) {
			int cur = static_cast<int>(this->dir) * 90;
			cur += angle;
			while (cur >= 360) {
				cur -= 360;
			}
			while (cur < 0) {
				cur += 360;
			}
			this->dir = static_cast<Direction>(cur/90);
		}

	public:
		// Constructor initializes initial position + direction
		Ship() {
			this->posX = 0;
			this->posY = 0;
			this->dir = Direction::East;
		}

		// Processes the given movement
		void processMove(const std::string & move) {
			// Get 'argument'
			int val = std::stoi(move.substr(1));

			// Take action based on first character
			switch (move[0]) {
				case 'N':
					this->posY -= val;
					break;

				case 'E':
					this->posX += val;
					break;

				case 'S':
					this->posY += val;
					break;

				case 'W':
					this->posX -= val;
					break;

				case 'L':
					this->rotate(-val);
					break;

				case 'R':
					this->rotate(val);
					break;

				case 'F':
					switch (this->dir) {
						case Direction::North:
							this->posY -= val;
							break;

						case Direction::East:
							this->posX += val;
							break;

						case Direction::South:
							this->posY += val;
							break;

						case Direction::West:
							this->posX -= val;
							break;
					}
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
