#include "solution.h"
#include <iostream>

int main(int argc, char *argv[]) {
  Solution s;

  // Case 1, expected true.
  auto res = s.run({1, 1, 0});
  std::cout << "Expected 1 actual " << res << std::endl;

  // Case 2, expected true.
  res = s.run({1, 10});
  std::cout << "Expected 1 actual " << res << std::endl;

  // Case 2, expected false.
  res = s.run({1, 0});
  std::cout << "Expected 0 actual " << res << std::endl;
  return 0;
}