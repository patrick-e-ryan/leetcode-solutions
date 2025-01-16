#include "solution.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  // Test Case 1
  std::string str = "abaacbcbb";
  Solution s;
  auto res = s.minimumLength(str);
  std::cout << "1. Expected 5, actual " << res << "\n";

  return 0;
}