// Advent of Code (2020) Day 17
#include <fstream>
#include <iostream>
#include <vector>

// Number of cycles to simulate
static constexpr size_t simulateCycles = 6;

// Grids
typedef std::vector< std::vector<bool> > Grid2D;
typedef std::vector<Grid2D> Grid3D;
typedef std::vector<Grid3D> Grid4D;

// Class handling the behaviour of the 'pocket dimension"
class PocketDimension {
    private:
        // 4D Grid
        Grid4D grid;

        // Index of 0th Z (only useful for printing)
        size_t zeroZIndex;

        // Add a 'boundary' for each dimension
        void addBorder() {
            // Temp plane
            Grid3D tmpZ = Grid3D();
            Grid2D tmpY = Grid2D();
            tmpY.resize(this->grid[0][0].size());
            for (size_t y = 0; y < tmpY.size(); y++) {
                tmpY[y].resize(this->grid[0][0][0].size(), false);
            }
            for (size_t z = 0; z < this->grid[0].size(); z++) {
                tmpZ.push_back(tmpY);
            }
            this->grid.insert(this->grid.begin(), tmpZ);
            this->grid.push_back(tmpZ);
            this->zeroZIndex++;

            // W
            for (size_t w = 0; w < this->grid.size(); w++) {
                // Temp plane
                Grid2D tmpY = Grid2D();
                tmpY.resize(this->grid[w][0].size());
                for (size_t y = 0; y < tmpY.size(); y++) {
                    tmpY[y].resize(this->grid[w][0][0].size(), false);
                }

                // Z
                this->grid[w].insert(this->grid[w].begin(), tmpY);
                this->grid[w].push_back(tmpY);

                // Y
                for (size_t z = 0; z < this->grid[w].size(); z++) {
                    this->grid[w][z].insert(this->grid[w][z].begin(), std::vector<bool>(this->grid[w][z][0].size()));
                    this->grid[w][z].push_back(std::vector<bool>(this->grid[w][z][0].size()));

                    // X
                    for (size_t y = 0; y < this->grid[w][z].size(); y++) {
                        this->grid[w][z][y].insert(this->grid[w][z][y].begin(), false);
                        this->grid[w][z][y].push_back(false);
                    }
                }
            }
        }

        // Returns the number of neighbouring 'active' cubes
        size_t countActiveNeighbours(int x, int y, int z, int w) {
            size_t active = 0;

            for (int pw = w-1; pw <= w+1; pw++) {
                // Skip out of bounds
                if (pw < 0 || pw >= this->grid.size()) {
                    continue;
                }

                for (int pz = z-1; pz <= z+1; pz++) {
                    // Skip out of bounds
                    if (pz < 0 || pz >= this->grid[pw].size()) {
                        continue;
                    }

                    for (int py = y-1; py <= y+1; py++) {
                        // Skip out of bounds
                        if (py < 0 || py >= this->grid[pw][pz].size()) {
                            continue;
                        }

                        for (int px = x-1; px <= x+1; px++) {
                            // Skip out of bounds
                            if (px < 0 || px >= this->grid[pw][pz][py].size()) {
                                continue;
                            }


                            // Don't count ourselves
                            if (px == x && py == y && pz == z && pw == w) {
                                continue;
                            }

                            active += (this->grid[pw][pz][py][px] ? 1 : 0);
                        }
                    }
                }
            }

            return active;
        }

    public:
        // Initialize with the given 2d data
        PocketDimension(const Grid2D & start) {
            this->grid.push_back(Grid3D());
            this->grid[0].push_back(start);
            this->zeroZIndex = 0;
        }

        // Simulate one cycle
        void simulate() {
            // Add a border for each dimension
            this->addBorder();

            // Create a copy to operate on
            Grid4D copy = this->grid;

            // Iterate over each position in the original grid
            for (size_t w = 0; w < this->grid.size(); w++) {
                for (size_t z = 0; z < this->grid[w].size(); z++) {
                    for (size_t y = 0; y < this->grid[w][z].size(); y++) {
                        for (size_t x = 0; x < this->grid[w][z][y].size(); x++) {
                            // Count number of active neighbours
                            size_t active = this->countActiveNeighbours(x, y, z, w);

                            // Alter based on puzzle requirements
                            if (this->grid[w][z][y][x] && !(active == 2 || active == 3)) {
                                copy[w][z][y][x] = false;

                            } else if (!this->grid[w][z][y][x] && active == 3) {
                                copy[w][z][y][x] = true;
                            }
                        }
                    }
                }
            }

            // Replace old with copy
            this->grid = copy;
        }

        // Print state
        void print() {
            // Print each pair of z, w dimensions
            for (size_t w = 0; w < this->grid.size(); w++) {
                for (size_t z = 0; z < this->grid[w].size(); z++) {
                    std::cout << "z=" << static_cast<int>(z - zeroZIndex) << ", w=" << static_cast<int>(w - zeroZIndex) << std::endl;

                    for (size_t y = 0; y < this->grid[w][z].size(); y++) {
                        for (size_t x = 0; x < this->grid[w][z][y].size(); x++) {
                            std::cout << (this->grid[w][z][y][x] ? "#" : ".");
                        }
                        std::cout << std::endl;
                    }

                    std::cout << std::endl;
                }
            }
        }

        // Return number of active
        size_t countActive() {
            size_t active = 0;

            for (size_t w = 0; w < this->grid.size(); w++) {
                for (size_t z = 0; z < this->grid[w].size(); z++) {
                    for (size_t y = 0; y < this->grid[w][z].size(); y++) {
                        for (size_t x = 0; x < this->grid[w][z][y].size(); x++) {
                            active += (this->grid[w][z][y][x] ? 1 : 0);
                        }
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