#include "solution.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  // Test Case 1, totally locked, imbalanced
  std::string str = "()()(((()(((()))))))))";
  std::string locked = "1111111111111111111111";
  Solution s;
  auto res = s.canBeValid(str, locked);
  std::cout << "1. Expected 0, actual " << res << "\n";

  // Test Case 2, totally locked, balanced but out of order.
  str = ")(";
  locked = "11";
  res = s.canBeValid(str, locked);
  std::cout << "2. Expected 0, actual " << res << "\n";

  // Test Case 3, totally locked, balanced but out of order.
  str = "(()))(()";
  locked = "11111111";
  res = s.canBeValid(str, locked);
  std::cout << "3. Expected 0, actual " << res << "\n";

  // Test Case 4, totally locked, balanced.
  str = "(())()(())";
  locked = "11111111";
  res = s.canBeValid(str, locked);
  std::cout << "4. Expected 1, actual " << res << "\n";

  // Test Case 5, solvable.
  str = "))()))";
  locked = "010100";
  res = s.canBeValid(str, locked);
  std::cout << "5. Expected 1, actual " << res << "\n";

  // Test Case 6, not solvable, edge case.
  str = ")";
  locked = "0";
  res = s.canBeValid(str, locked);
  std::cout << "6. Expected 0, actual " << res << "\n";

  // Test Case 7, solvable.
  str = ")()()()(";
  locked = "00000000";
  res = s.canBeValid(str, locked);
  std::cout << "7. Expected 1, actual " << res << "\n";

  // Test Case 8, solvable.
  str = ")()()()(";
  locked = "01100100";
  res = s.canBeValid(str, locked);
  std::cout << "8. Expected 1, actual " << res << "\n";

  return 0;
}