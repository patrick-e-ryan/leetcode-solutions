#include "solution.h"

/**
This is a simple sliding window problem, where we greedily consume `nums` until
the bitwise AND is nonzero. At this point, we restart our sliding window at the
offending entry, and begin our search again, keeping track of the longest
subarray found so far. This yields an O(n) time and O(1) space complexity
solution. We take at most 2n iterations to complete.
*/
int Solution::run(std::vector<int> &nums) {
  if (nums.size() == 0 || nums.size() == 1) {
    return nums.size();
  }

  auto start = 0;
  auto end = 1;

  auto longest = 1;
  auto mask = nums[0];
  while (end != nums.size()) {
    auto n = nums[end];
    // Note that a number will have a pairwise bitwise AND of zero with all
    // elements of a subarray if and only if it has a bitwise AND of zero with
    // the bitwise OR of all elements in the subarray. Further, we do not need
    // to check the case where end == start, as mask would be zero, leading to
    // this AND always being zero.
    if (mask & nums[end]) {
      // Record length if it is the longest, then reset.
      if ((end - start) > longest) {
        longest = end - start;
      }
      // Remove nums[start] from our mask, then test again.
      mask ^= nums[start];
      start++;
    } else {
      // Extend our subarray, adding the new value to our mask.
      mask |= nums[end];
      end++;
    }
  }
  if ((end - start) > longest) {
    longest = end - start;
  }
  return longest;
}
