#include "solution.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  // Test Case 1
  std::vector<int> a{1, 2, 3, 7, 6, 5, 4};
  std::vector<int> b{2, 1, 4, 7, 6, 5, 3};
  Solution s;
  auto res = s.findThePrefixCommonArray(a, b);
  std::cout << "[";
  for (const auto &v : res) {
    std::cout << v << ", ";
  }
  std::cout << "]" << std::endl;

  return 0;
}