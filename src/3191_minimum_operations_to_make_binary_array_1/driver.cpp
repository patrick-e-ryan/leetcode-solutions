#include "solution.h"

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  Solution s;
  std::vector<int> nums = {0, 1, 1, 1, 0, 0};
  auto result = s.run(nums);
  std::cout << "Test case 1. Expected 3, actual " << result << std::endl;

  nums = {0, 1, 1, 1};
  result = s.run(nums);
  std::cout << "Test case 2. Expected -1, actual " << result << std::endl;
  return 0;
}