// Advent of Code (2020): Day 9
#include <fstream>
#include <iostream>
#include <vector>

// Invalid number determined from part 1
static constexpr size_t invalidNum = 675280050;

// Returns a pair of <min, max> of the numbers that form the subset of numbers
// that equal the passed value
// Returns <0, 0> if none found
static std::pair<size_t, size_t> haveContiguousSum(const std::vector<size_t> nums, const size_t num) {
	size_t sum = 0;
	size_t min = 0;
	size_t max = 0;

	// Pick a start and end position
	for (size_t start = 0; start < nums.size()-1; start++) {
		sum = nums[start];
		min = sum;
		max = sum;
		for (size_t end = start+1; end < nums.size(); end++) {
			// Update all values
			sum += nums[end];
			if (nums[end] < min) {
				min = nums[end];
			}
			if (nums[end] > max) {
				max = nums[end];
			}

			// Check if equal and return pair
			if (sum == num) {
				return std::pair<size_t, size_t>(min, max);
			}
		}
	}

	return std::pair<size_t, size_t>(0, 0);
}

int main(void) {
	// Vector to store encountered numbers
	std::vector<size_t> numbers;

	// Iterate over each line, appending each number to the vector
	// This breaks when a contiguous set of numbers at up to the
	// required number
	std::ifstream file("input.txt");
	size_t num;
	while (file >> num) {
		// Add to vector
		numbers.push_back(num);

		// If there's a set then print out the sum of the first and last number
		std::pair<size_t, size_t> nums = haveContiguousSum(numbers, invalidNum);
		if (nums.first != 0 && nums.second != 0) {
			std::cout << "The weakness is: " << nums.first + nums.second << std::endl;
			return 0;
		}
	}

	std::cout << "No contiguous sum found" << std::endl;
	return 0;
}
