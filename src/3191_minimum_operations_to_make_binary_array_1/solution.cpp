#include "solution.h"

/**
This is a simple single-pass algorithm that can be solved with some basic
inductive logic. let `i` be the location of the first zero in the array. Then,
we must flip `i`, `i + 1`, and `i + 2`. This flip *must* occur, and we perform
exactly one flip on `i`. Hence, the subarray `[0, i]` has had the minimal number
of flips applied to make it all one. We may then consider the subarray `[i + 1,
n]`, and perform the same operation. If one proved the base case for `n=3, 4, 5`
(corresponding to the "second half" sub-arrays of length 0, 1, and 2)
respectively, we can claim inductively that the subarray `[i + 1, n]` may be
flipped in an identical manner minimally.

While this is formally provable, it's much simpler to think about the intuitive
loop invariant that the subarray `[0, i]` has had the minimal number of flips
applied to it, and that invariant is not broken throughout iteration, leading to
an overall minimum number of iterations applied.
*/
int Solution::run(std::vector<int> &nums) {
  auto n = nums.size();
  auto count = 0;
  for (auto i = 0; i < (n - 2); ++i) {
    if (!nums[i]) {
      // Perform flip.
      nums[i] = 1;
      nums[i + 1] = !nums[i + 1];
      nums[i + 2] = !nums[i + 2];
      count++;
    }
  }
  // Assert our last 3 elements are non-zero
  if ((nums[n - 3] != 1) || (nums[n - 2] != 1) || (nums[n - 1] != 1)) {
    return -1;
  }
  return count;
}
