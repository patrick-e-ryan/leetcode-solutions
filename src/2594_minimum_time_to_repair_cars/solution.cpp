#include "solution.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdint>

constexpr inline uint64_t cost(uint64_t rank, uint64_t n) {
  return rank * n * n;
}

/// It is possible for a queue of rank `r` to complete `n` items in time `t =
/// rn^2`, leading to `n = sqrt(t/r)`, rounded down to the nearest integer.
constexpr inline uint64_t cars_repaired(double rank, double time) {
  return std::floor(std::sqrt(time / rank));
}

constexpr inline uint64_t total_cars_repaired(const std::vector<int> &ranks,
                                              uint64_t time) {
  return std::ranges::fold_left(ranks, 0,
                                [time](uint64_t total, uint64_t rank) {
                                  return total + cars_repaired(rank, time);
                                });
}

/**
This problem reduces down to performing a binary search on the space of possible
times it takes to repair all the cars. We know that the fastest mechanic can
repair all vehicles in `r * n^2` time, but we may be able to divide the work
among other mechanics to increase speed. For a given time `t`, we calculate the
number of vehicles that can be repaired with all mechanics. If this value is
greater than or equal to the number of vehicles, this is a new candidate for the
minimum time required, and we may reduce our search space to `[1, t]`.
Otherwise, we know that it is not possible to fix all cars in `t`, and the
search space becomes `[t, max]`. We terminate our search when the binary search
midpoint stabilizes on a solution.
*/
long long Solution::run(std::vector<int> &ranks, int cars) {
  // Fast path
  if (ranks.size() == 1) {
    return cost(ranks.front(), cars);
  }
  uint64_t min = 1ull;

  // Scan ranks array to find the fastest queue, and compute the absolte maximum
  // time to complete (r * cars^2)
  uint64_t max = cost(*std::ranges::min_element(ranks), cars);

  // We can perform a binary search over the amount of time required, with the
  // discriminant being whether the cars can be repaired or not in time `t`.
  uint64_t old_midpoint = 0;
  uint64_t midpoint = INT_MAX;
  uint64_t counter = 0;
  while (old_midpoint != midpoint) {
    counter++;
    old_midpoint = midpoint;
    midpoint = (min + max) / 2;
    auto num_repaired = total_cars_repaired(ranks, midpoint);
    if (num_repaired >= cars) {
      // We found a new valid maximum time.
      max = midpoint;
    } else {
      // New minimum time.
      min = midpoint;
    }
  }

  return max; // max is always guaranteed to be valid, min never valid.
}
