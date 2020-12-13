// Advent of Code (2020) Day 11
#include <fstream>
#include <iostream>
#include <vector>

// Enumeration for 'tile' type
enum class Seat {
	None,		// No seat is in the tile
	Empty,		// Seat is empty
	Occupied	// Seat is occupied
};

// Ferry class, contains grid of seats which can be 'simulated'
class Ferry {
	private:
		// 2D array representing seats
		std::vector< std::vector<Seat> > seats;

		// Return number of adjacent seats that are occupied
		size_t adjacentOccupiedSeats(const int row, const int col) {
			size_t occupied = 0;

			for (int x = col-1; x <= col+1; x++) {
				for (int y = row-1; y <= row+1; y++) {
					// Don't check invalid locations
					if ((x == col && y == row) || x < 0 || x >= this->seats[0].size() || y < 0 || y >= this->seats.size()) {
						continue;
					}

					if (this->seats[y][x] == Seat::Occupied) {
						occupied++;
					}
				}
			}

			return occupied;
		}

	public:
		// Constructor accepts 2D array of seats (represented by chars
		// as explained in the description)
		Ferry(const std::vector<std::string> & input) {
			// Iterate over and convert
			for (const std::string row : input) {
				std::vector<Seat> tmp;

				for (const char seat : row) {
					switch (seat) {
						case '.':
							tmp.push_back(Seat::None);
							break;

						case 'L':
							tmp.push_back(Seat::Empty);
							break;

						case '#':
							tmp.push_back(Seat::Occupied);
							break;
					}
				}

				this->seats.push_back(tmp);
			}
		}

		// Simulate people 'moving' seats
		// Returns whether changed or not
		bool simulateSeating() {
			// Create copy to operate on
			bool changed = false;
			std::vector< std::vector<Seat> > newSeats = this->seats;

			// Iterate over each seat, changing if needed
			for (size_t row = 0; row < this->seats.size(); row++) {
				for (size_t col = 0; col < this->seats[row].size(); col++) {
					// Skip over floor
					if (this->seats[row][col] == Seat::None) {
						continue;
					}

					size_t count = this->adjacentOccupiedSeats(row, col);
					if (this->seats[row][col] == Seat::Empty && count == 0) {
						newSeats[row][col] = Seat::Occupied;
						changed = true;

					} else if (this->seats[row][col] == Seat::Occupied && count >= 4) {
						newSeats[row][col] = Seat::Empty;
						changed = true;
					}
				}
			}

			// Update and return
			this->seats = newSeats;
			return changed;
		}

		// Return number of occupied seats
		size_t occupiedSeats() {
			size_t occupied = 0;

			for (const std::vector<Seat> row : this->seats) {
				for (const Seat seat : row) {
					if (seat == Seat::Occupied) {
						occupied++;
					}
				}
			}

			return occupied;
		}
};

int main(void) {
	// Read input and create 'Ferry' object
	std::vector<std::string> input;
	std::ifstream file("input.txt");
	std::string row;
	while (file >> row) {
		input.push_back(row);
	}
	Ferry ferry(input);

	// Simulate until no one changes seat
	bool changed = false;
	do {
		changed = ferry.simulateSeating();
	} while (changed);

	// Print results
	std::cout << "There are " << ferry.occupiedSeats() << " occupied seats" << std::endl;
	return 0;
}
