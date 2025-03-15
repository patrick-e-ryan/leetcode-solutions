#include "solution.h"
#include <iostream>

int main(int argc, char *argv[]) {
  Solution s;

  // Test Case 1, expected 3
  std::vector<std::vector<int>> test_case = {
      {1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}};
  auto result = s.run(test_case);
  std::cout << "Test 1. Expected 3, actual " << result << std::endl;
  test_case = {{1, 1, 3}, {3, 2, 2}, {1, 1, 4}};
  result = s.run(test_case);
  std::cout << "Test 2. Expected 0, actual " << result << std::endl;
  test_case = {{1, 2}, {4, 3}};
  result = s.run(test_case);
  std::cout << "Test 3. Expected 1, actual " << result << std::endl;
  return 0;
}