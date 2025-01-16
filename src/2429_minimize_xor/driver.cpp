#include "solution.h"
#include <iostream>

int main(int argc, char *argv[]) {
  // Test Case 1
  int n1 = 3;
  int n2 = 5;
  Solution s;
  auto res = s.minimizeXor(n1, n2);
  std::cout << "1. Expected 3. Actual " << res << std::endl;

  n1 = 1;
  n2 = 12;
  res = s.minimizeXor(n1, n2);
  std::cout << "2. Expected 3. Actual " << res << std::endl;

  return 0;
}