// Advent of Code (2020) Day 17
#include <fstream>
#include <iostream>
#include <vector>

// Number of cycles to simulate
static constexpr size_t simulateCycles = 6;

// 2D Grid
typedef std::vector< std::vector<bool> > Grid2D;

// Class handling the behaviour of the 'pocket dimension"
class PocketDimension {
    private:
        // 3D Grid simply contains multiple 2D grids
        std::vector<Grid2D> grid;

        // Index of 0th Z (only useful for printing)
        size_t zeroZIndex;

        // Returns the number of neighbouring 'active' cubes
        size_t countActiveNeighbours(int x, int y, int z) {
            size_t active = 0;

            for (int pz = z-1; pz <= z+1; pz++) {
                // Skip out of bounds
                if (pz < 0 || pz >= this->grid.size()) {
                    continue;
                }

                for (int py = y-1; py <= y+1; py++) {
                    // Skip out of bounds
                    if (py < 0 || py >= this->grid[pz].size()) {
                        continue;
                    }

                    for (int px = x-1; px <= x+1; px++) {
                        // Skip out of bounds
                        if (px < 0 || px >= this->grid[pz][py].size()) {
                            continue;
                        }

                        // Don't count ourselves
                        if (px == x && py == y && pz == z) {
                            continue;
                        }

                        active += (this->grid[pz][py][px] ? 1 : 0);
                    }
                }
            }

            return active;
        }

    public:
        // Initialize with the given 2d data
        PocketDimension(const Grid2D & start) {
            this->grid.push_back(start);
            this->zeroZIndex = 0;
        }

        // Simulate one cycle
        void simulate() {
            // Add a 'boundary' for each dimension (this is bad but should be fine?)
            // Temp plane
            Grid2D tmp = Grid2D();
            tmp.resize(this->grid[0].size());
            for (size_t y = 0; y < tmp.size(); y++) {
                tmp[y].resize(this->grid[0][0].size(), false);
            }

            // Z
            this->grid.insert(this->grid.begin(), tmp);
            this->grid.push_back(tmp);
            this->zeroZIndex++;

            // Y
            for (size_t z = 0; z < this->grid.size(); z++) {
                this->grid[z].insert(this->grid[z].begin(), std::vector<bool>(this->grid[z][0].size()));
                this->grid[z].push_back(std::vector<bool>(this->grid[z][0].size()));

                // X
                for (size_t y = 0; y < this->grid[z].size(); y++) {
                    this->grid[z][y].insert(this->grid[z][y].begin(), false);
                    this->grid[z][y].push_back(false);
                }
            }

            // Create a copy to operate on
            std::vector<Grid2D> copy = this->grid;

            // Iterate over each position in the original grid
            for (size_t z = 0; z < this->grid.size(); z++) {
                for (size_t y = 0; y < this->grid[z].size(); y++) {
                    for (size_t x = 0; x < this->grid[z][y].size(); x++) {
                        // Count number of active neighbours
                        size_t active = this->countActiveNeighbours(x, y, z);

                        // Alter based on puzzle requirements
                        if (this->grid[z][y][x] && !(active == 2 || active == 3)) {
                            copy[z][y][x] = false;

                        } else if (!this->grid[z][y][x] && active == 3) {
                            copy[z][y][x] = true;
                        }
                    }
                }
            }

            // Replace old with copy
            this->grid = copy;
        }

        // Print state
        void print() {
            // Print each z dimension
            for (size_t z = 0; z < this->grid.size(); z++) {
                std::cout << "z=" << static_cast<int>(z - zeroZIndex) << std::endl;

                for (size_t y = 0; y < this->grid[z].size(); y++) {
                    for (size_t x = 0; x < this->grid[z][y].size(); x++) {
                        std::cout << (this->grid[z][y][x] ? "#" : ".");
                    }
                    std::cout << std::endl;
                }

                std::cout << std::endl;
            }
        }

        // Return number of active
        size_t countActive() {
            size_t active = 0;

            for (size_t z = 0; z < this->grid.size(); z++) {
                for (size_t y = 0; y < this->grid[z].size(); y++) {
                    for (size_t x = 0; x < this->grid[z][y].size(); x++) {
                        active += (this->grid[z][y][x] ? 1 : 0);
                    }
                }
            }

            return active;
        }
};

int main(void) {
    // Form grid from input
    Grid2D grid;
    std::ifstream file("input.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::vector<bool> gridLine;

        for (const char c : line) {
            gridLine.push_back(c == '#');
        }

        grid.push_back(gridLine);
    }

    // Create 'dimension'
    PocketDimension dim = PocketDimension(grid);
    std::cout << "Before any cycles: " << std::endl << std::endl;
    dim.print();

    // Simulate
    for (size_t i = 0; i < simulateCycles; i++) {
        dim.simulate();

        std::cout << "\nAfter cycle: " << i+1 << std::endl;
        dim.print();
    }

    // Print results
    std::cout << "Active cubes: " << dim.countActive() << std::endl;
    return 0;
}