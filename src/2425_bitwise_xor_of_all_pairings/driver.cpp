#include "solution.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  // Test Case 1
  auto n1 = std::vector<int>{1, 2, 4, 5, 6, 7, 12, 4, 6, 1, 5};
  auto n2 = std::vector<int>{1, 2, 4, 5, 6, 7, 12, 4, 6, 1, 5};
  Solution s;
  auto res = s.xorAllNums(n1, n2);
  std::cout << "1. Expected 0, actual " << res << std::endl;

  return 0;
}