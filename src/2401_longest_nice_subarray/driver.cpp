#include "solution.h"

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  Solution s;

  std::vector<int> nums = {1, 3, 8, 48, 10};
  auto result = s.run(nums);
  std::cout << "Test case 1, expected 3, actual " << result << std::endl;

  nums = {3, 1, 5, 11, 13};
  result = s.run(nums);
  std::cout << "Test case 2, expected 1, actual " << result << std::endl;

  nums = {1, 2, 4,  8,  16, 32,  64,  128, 256,  5,   2,
          4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
  result = s.run(nums);
  std::cout << "Test case 3, expected 11, actual " << result << std::endl;
  return 0;
}