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
		// (first seat in each direction)
		size_t adjacentOccupiedSeats(const int row, const int col) {
			size_t occupied = 0;
			int i;

			// Up
			for (i = row-1; i >= 0; i--) {
				if (this->seats[i][col] == Seat::Occupied) {
					occupied++;
					break;
				} else if (this->seats[i][col] == Seat::Empty) {
					break;
				}
			}

			// Up + Right
			for (i = 1; row-i >= 0 && col+i < this->seats[0].size(); i++) {
				if (this->seats[row-i][col+i] == Seat::Occupied) {
					occupied++;
					break;
				} else if (this->seats[row-i][col+i] == Seat::Empty) {
					break;
				}
			}

			// Right
			for (i = col+1; i < this->seats[row].size(); i++) {
				if (this->seats[row][i] == Seat::Occupied) {
					occupied++;
					break;
				} else if (this->seats[row][i] == Seat::Empty) {
					break;
				}
			}

			// Down + Right
			for (i = 1; row+i < this->seats.size() && col+i < this->seats[0].size(); i++) {
				if (this->seats[row+i][col+i] == Seat::Occupied) {
					occupied++;
					break;
				} else if (this->seats[row+i][col+i] == Seat::Empty) {
					break;
				}
			}

			// Down
			for (i = row+1; i < this->seats.size(); i++) {
				if (this->seats[i][col] == Seat::Occupied) {
					occupied++;
					break;
				} else if (this->seats[i][col] == Seat::Empty) {
					break;
				}
			}

			// Down + Left
			for (i = 1; row+i < this->seats.size() && col-i >= 0; i++) {
				if (this->seats[row+i][col-i] == Seat::Occupied) {
					occupied++;
					break;
				} else if (this->seats[row+i][col-i] == Seat::Empty) {
					break;
				}
			}

			// Left
			for (i = col-1; i >= 0; i--) {
				if (this->seats[row][i] == Seat::Occupied) {
					occupied++;
					break;
				} else if (this->seats[row][i] == Seat::Empty) {
					break;
				}
			}

			// Up + Left
			for (i = 1; row-i >= 0 && col-i >= 0; i++) {
				if (this->seats[row-i][col-i] == Seat::Occupied) {
					occupied++;
					break;
				} else if (this->seats[row-i][col-i] == Seat::Empty) {
					break;
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

					} else if (this->seats[row][col] == Seat::Occupied && count >= 5) {
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
