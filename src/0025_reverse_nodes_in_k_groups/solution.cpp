#include "solution.h"

/**
This solution is O(1) in space complexity, as requested.
*/
ListNode *Solution::run(ListNode *head, int k) {
  constexpr ListNode *sentinel = nullptr;
  ListNode *curr_head = nullptr;
  ListNode *curr_tail = nullptr;
  ListNode *previous_tail = nullptr;
  ListNode *previous_head = nullptr;

  while (head != nullptr) {
    // Reverse k nodes, keeping track of the tail of this sub-list. We will use
    // it to attach later.
    curr_head = sentinel;
    curr_tail = head;
    // Check we can consume k nodes.
    bool can_consume = true;
    {
      auto *tmp_next = head;
      for (auto i = 0; i < k; ++i) {
        if (tmp_next == nullptr) {
          can_consume = false;
          break;
        }
        tmp_next = tmp_next->next;
      }
    }

    if (can_consume) {
      for (auto i = 0; i < k; ++i) {
        auto next = head->next;
        head->next = curr_head;
        curr_head = head;
        head = next;
      }
    } else {
      curr_head = head;
      head = nullptr;
    }

    // Attach our previous sub-list to this sub-list.
    if (previous_tail) {
      previous_tail->next = curr_head;
    }

    if (!previous_head) {
      // store the new base of our list.
      previous_head = curr_head;
    }

    // Update previous sub-list.
    previous_tail = curr_tail;
  }
  return previous_head;
}
