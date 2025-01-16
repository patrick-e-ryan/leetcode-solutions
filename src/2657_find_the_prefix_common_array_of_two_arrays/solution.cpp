#include "solution.h"

#include <bitset>
#include <vector>

std::vector<int> Solution::findThePrefixCommonArray(std::vector<int> &A,
                                                    std::vector<int> &B) {
  // This can readily be solved with a pair of bitsets, counting the number of
  // bits set in the logical AND of the two after each iteration (i.e., both
  // arrays have the value present).
  constexpr auto max_size = 50 + 1; // our permutations are 1-based.
  std::bitset<max_size> a_set;
  std::bitset<max_size> b_set;

  // Bail on bad input.
  if (A.size() > max_size || B.size() > max_size || A.size() != B.size()) {
    abort();
  }

  std::vector<int> result;

  for (auto i = 0; i < A.size(); ++i) {
    a_set[A[i]] = true;
    b_set[B[i]] = true;
    result.push_back((a_set & b_set).count());
  }
  return result;
}