#include "solution.h"

#include <algorithm>
#include <numeric>
#include <vector>

int Solution::minimumLength(std::string s) {
  // Inductively, one can see that any odd number of letters will reduce to
  // one, and any even number of letters will reduce to two. Count all these
  // up and we have our final answer.

  std::vector<int> frequencies(26);
  std::for_each(s.begin(), s.end(),
                [&frequencies](char c) { frequencies[c - 'a']++; });

  return std::transform_reduce(frequencies.begin(), frequencies.end(), 0,
                               std::plus{},        // reduce
                               [](auto x) -> int { // transform
                                 if (x == 0)
                                   return 0;
                                 return (x % 2) == 0 ? 2 : 1;
                               });
}