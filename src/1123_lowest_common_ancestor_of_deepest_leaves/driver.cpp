#include "solution.h"
#include <iostream>
#include <memory>
#include <vector>

TreeNode *build_tree_recursive(std::vector<std::unique_ptr<TreeNode>> &storage,
                               const std::vector<int> &values, int loc) {
  // OOB, we're at a leaf.
  if (loc >= values.size()) {
    return nullptr;
  }

  // Missing node.
  if (values[loc] == -1) {
    return nullptr;
  }

  storage.push_back(std::make_unique<TreeNode>(values[loc]));
  auto tmp = storage.back().get();
  tmp->left = build_tree_recursive(storage, values, 2 * loc + 1);
  tmp->right = build_tree_recursive(storage, values, 2 * loc + 2);
  return tmp;
}

/*
Recursively build a tree of TreeNode from `values`. The returned vector will
hold unique pointers to each node, with index zero representing the root.
Releasing the vector will destroy the entire tree.
*/
std::vector<std::unique_ptr<TreeNode>>
build_tree(const std::vector<int> &values) {
  std::vector<std::unique_ptr<TreeNode>> result;
  build_tree_recursive(result, values, 0);
  return result;
}

/*
NOTE, we blindly ignore memory leaks since this is just a dummy test driver.
*/
int main(int argc, char *argv[]) {
  Solution s;
  auto storage = build_tree({3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4});

  auto *tree = storage[0].get();
  auto result = s.run(tree);
  if (result) {
    std::cout << "Test case 1. Expected 2, actual: " << result->val
              << std::endl;
  }
  storage = build_tree({1});
  tree = storage[0].get();
  result = s.run(tree);
  if (result) {
    std::cout << "Test case 2. Expected 1, actual: " << result->val
              << std::endl;
  }

  storage = build_tree({0, 1, 3, -1, 2});
  tree = storage[0].get();
  result = s.run(tree);
  if (result) {
    std::cout << "Test case 3. Expected 2, actual: " << result->val
              << std::endl;
  }
  return 0;
}