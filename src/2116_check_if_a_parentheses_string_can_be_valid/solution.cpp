#include "solution.h"
#include <stack>
#include <string>

static bool canBeValidFast(std::string s, std::string locked);

static bool is_valid(const std::string &str) {
  // Sum up the `(` and `)` in our string, returning the "balance value".
  auto count = 0;
  for (const auto &c : str) {
    switch (c) {
    case '(':
      count += 1;
      break;
    case ')':
      count -= 1;
      if (count < 0) {
        return false;
      }
      break;
    default:
      // Unsupported.
      abort();
    }
  }
  return count == 0;
}

/**
This problem is a twist on the classic balanced parentheses problem. The
original problem can be solved with a simple integer count in O(1) space and
O(n) time, where `n` is the length of the input string. When a `(` is
encountered, inrement the count, and when `)` is encountered, decrement. If the
count is ever negative, we fail, and if the count is non-zero after processing,
we fail. This problem can also be solved via a stack, pushing and popping from
it as oppose to incrementing/decrementing a counter.

The twist to this problem is that we can mutate the string along the way,
dependent upon the value of `locked[i]`, where `i` is the current location in
the string. As such, we can potentially fix any imbalances along the way.

We can perform two passes on the string (forward and backward) to perform an
initial set of fixes, then pair up any remaining unlocked characters. We can do
this in O(1) space by maintaining two counters: num_open and num_unlocked. We
opt for two stacks for clarity.

*/
bool Solution::canBeValid(std::string s, std::string locked) {
  if (use_fast) {
    return canBeValidFast(s, locked);
  }
  if (is_valid(s)) {
    // Nothing to do.
    return true;
  }

  std::stack<int> unlocked;
  std::stack<int> open;

  for (auto i = 0; i < s.size(); ++i) {
    // Push wildcards for later use.
    if (locked[i] == '0') {
      unlocked.push(i);
      continue;
    }

    char c = s[i];
    if (c == '(') {
      open.push(i);
    } else { // ')'
      // Can we close a parentheses off?
      if (!open.empty()) {
        open.pop();

      } else if (!unlocked.empty()) { // Can we consume a wildcard?
        unlocked.pop();
      } else {
        return false;
      }
    }
  }

  // Now, fixup any remaining open parentheses. We can only use unlocked entires
  // after the open.
  while (!open.empty() && !unlocked.empty() && open.top() < unlocked.top()) {
    open.pop();
    unlocked.pop();
  }

  // If we used up all open parens, we are OK. We also need an even number of
  // unlocked to balance themselves out.
  return open.empty() && unlocked.size() % 2 == 0;
}

// static bool canBeValidFast(std::string s, std::string locked) {

//   int length = s.size();
//   // If length of string is odd, return false.
//   if (length % 2 == 1) {
//     return false;
//   }
//   int openBrackets = 0, unlocked = 0;
//   // Iterate through the string to handle '(' and ')'.
//   for (int i = 0; i < length; i++) {
//     if (locked[i] == '0') {
//       unlocked++;
//     } else if (s[i] == '(') {
//       openBrackets++;
//     } else if (s[i] == ')') {
//       if (openBrackets > 0) {
//         openBrackets--;
//       } else if (unlocked > 0) {
//         unlocked--;
//       } else {
//         return false;
//       }
//     }
//   }
//   // Match remaining open brackets with unlocked characters.
//   int balance = 0;
//   for (int i = length - 1; i >= 0; i--) {
//     if (locked[i] == '0') {
//       balance--;
//       unlocked--;
//     } else if (s[i] == '(') {
//       balance++;
//       openBrackets--;
//     } else if (s[i] == ')') {
//       balance--;
//     }
//     if (balance > 0) {
//       return false;
//     }
//     if (unlocked == 0 and openBrackets == 0) {
//       break;
//     }
//   }

//   if (openBrackets > 0) {
//     return false;
//   }

//   return true;
// }

static bool canBeValidFast(std::string s, std::string locked) {
  if (is_valid(s)) {
    // Nothing to do.
    return true;
  }

  int unlocked;
  int open;
  int length = s.size();
  // If length of string is odd, return false.
  if (length % 2 == 1) {
    return false;
  }
  // Iterate through the string to handle '(' and ')'.
  for (int i = 0; i < length; i++) {
    if (locked[i] == '0') {
      unlocked++;
    } else if (s[i] == '(') {
      open++;
    } else if (s[i] == ')') {
      if (open > 0) {
        open--;
      } else if (unlocked > 0) {
        unlocked--;
      } else {
        return false;
      }
    }
  }

  // Now, fixup any remaining open parentheses. We can only use unlocked
  // entires
  // after the open, so we iterate backwards.
  int total_balance = 0;
  for (int i = s.size() - 1; i >= 0; --i) {
    // "Consume" unlocked, decrementing total_balance. This can go negative
    // to
    // retroactively be consumed if needed.
    if (locked[i] == '0') {
      unlocked--;
      total_balance--;
    } else if (s[i] == '(') {
      // Consume an open paren.
      open--;
      total_balance++;
    } else if (s[i] == ')') {
      // Consume a close paren.
      total_balance--;
    }

    // If we cannot balance out, fail.
    if (total_balance > 0) {
      return false;
    }

    // If we've consumed all open and unlocked, terminate.
    if (!open && !unlocked) {
      break;
    }
  }

  // open can be <= 0 for valid cases. All we really care about
  // is the case where we have too many open parentheses.
  return open <= 0;
}
