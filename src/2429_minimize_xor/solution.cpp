#include "solution.h"

#include <bitset>

int Solution::minimizeXor(int num1, int num2) {
  /* This problem can be solved greedily in two "passes" over num1.
   * First, let `n` = the number of bits set in num2.
   *
   * On our first pass, start from the most significant bits in num1. Let the
   * current bit be `b`.
   *
   * If b == 0, do nothing. Otherwise, set b == 1 in our result and decrement n.
   * If n == 0, return result.
   *
   * If n > 0 after the first pass, start from the least significant bit in
   * num1. if b == 0, set it to 1 and decrement n.
   */
  constexpr auto bits_in_int = 8 * sizeof(int);

  std::bitset<bits_in_int> result(0);
  std::bitset<bits_in_int> comparator(num1);

  auto n = std::bitset<bits_in_int>(num2).count();

  // First pass, set 1's present in comparator.
  for (int i = bits_in_int - 1; i >= 0; --i) {
    if (n == 0) {
      break;
    }
    if (comparator.test(i)) {
      result.flip(i);
      n--;
    }
  }

  if (n == 0) {
    return static_cast<int>(result.to_ulong());
  }

  // Second pass, set 0's present in comparator to 1 from low->high to keep
  // minimum.
  for (auto i = 0; i < bits_in_int; ++i) {
    if (n == 0) {
      break;
    }
    if (!comparator.test(i)) {
      result.flip(i);
      n--;
    }
  }

  // Truncation is safe, we enforce the bitset can be held in an int.
  return static_cast<int>(result.to_ulong());
}