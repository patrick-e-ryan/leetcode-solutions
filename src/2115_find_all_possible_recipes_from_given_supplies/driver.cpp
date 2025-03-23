#include "solution.h"

#include <iostream>

void print_result(std::vector<std::string> res) {
  std::cout << "Buildable recipes:\n";
  for (const auto &r : res) {
    std::cout << "    " << r << "\n";
  }

  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  Solution s;
  std::vector<std::string> recipes = {"bread"};
  std::vector<std::vector<std::string>> ingredients = {{"yeast", "flour"}};
  std::vector<std::string> supplies = {"yeast", "flour", "corn"};
  auto res = s.run(recipes, ingredients, supplies);
  std::cout << "Test Case 1. Expected ['bread'], actual " << std::endl;
  print_result(res);

  recipes = {"bread", "sandwich"};
  ingredients = {{"yeast", "flour"}, {"bread", "meat"}};
  supplies = {"yeast", "flour", "meat"};
  res = s.run(recipes, ingredients, supplies);
  std::cout << "Test Case 2. Expected ['bread', 'sandwich'], actual "
            << std::endl;
  print_result(res);

  recipes = {"bread", "sandwich", "burger"};
  ingredients = {
      {"yeast", "flour"}, {"bread", "meat"}, {"sandwich", "meat", "bread"}};
  supplies = {"yeast", "flour", "meat"};
  res = s.run(recipes, ingredients, supplies);
  std::cout << "Test Case 3. Expected ['bread', 'sandwich', 'burger'], actual "
            << std::endl;
  print_result(res);

  return 0;
}