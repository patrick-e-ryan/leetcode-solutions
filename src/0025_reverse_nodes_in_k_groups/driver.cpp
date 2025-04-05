#include "solution.h"
#include <algorithm>
#include <iostream>
#include <vector>

ListNode *create_list(std::vector<int> node_values) {
  // [1,2,3,4,5] needs to be inserted 5, 4, 3, 2, 1
  std::reverse(node_values.begin(), node_values.end());
  ListNode *head = nullptr;
  for (auto val : node_values) {
    ListNode *n = new ListNode(val);
    n->next = head;
    head = n;
  }
  return head;
}

void print_list(ListNode *list) {
  std::cout << "[";
  auto n = list;
  while (n) {
    std::cout << n->val << ", ";
    n = n->next;
  }
  std::cout << "]" << std::endl;
}

int main(int argc, char *argv[]) {
  Solution s;

  // NOTE: This leaks all memory, we don't care as this is just a dumb test
  // runner.
  auto *test_case = create_list({1, 2, 3, 4, 5});
  auto k = 5;
  auto res = s.run(test_case, k);
  print_list(res);

  test_case = create_list({1, 2, 3, 4, 5});
  k = 2;
  res = s.run(test_case, k);
  print_list(res);

  test_case = create_list({1, 2, 3, 4, 5});
  k = 3;
  res = s.run(test_case, k);
  print_list(res);

  return 0;
}