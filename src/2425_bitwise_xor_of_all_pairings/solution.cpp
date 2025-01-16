#include "solution.h"
#include <functional>
#include <numeric>
#include <vector>

static int xor_elements(std::vector<int> v) {
  return std::reduce(v.begin(), v.end(), 0, std::bit_xor<>{});
}

/*
This problem is more of a riddle than a programming problem. It's important
to note that the XOR operation is both commutative and associative. Thus,
for an expression like:

  (a ^ b) ^ (c ^ d),

we can freely reorganize the variables. Further, for any integer n, n ^ n == 0.
It follows that applying XOR to n an odd number of times to itself is equal to n
and an even number of times is equal to 0.

This problem is asking for the result of the following expression:

  (n1 ^ m1) ^ (n1 ^ m2) ^ ... ^(n1 ^ mk) ^ (n2 ^ m1) ... ^(nl ^ mk)

where ni is an element in nums1, mi is an element in nums2, l == size(nums1),
and k == size(nums2). Each ni appears k times, and each mi appears l times. We
rearrange to:

  (n1 ^ n1 ^ ...) ^ ... ^ (nl ^ nl ^ ...) ^ (m1 ^ m1 ^ ...) ^ ...

If k is even, this reduces to
  (m1 ^ m1 ^ ...) ^ (m2 ^ ...) ^ ... ^ (mk ^ ...)

If l is even, we reduce to zero. If k is odd, the ni terms reduce to
(n1 ^ n2 ^ n3 ^ ...), and likewise for mi if l is odd.
*/
int Solution::xorAllNums(std::vector<int> &nums1, std::vector<int> &nums2) {
  int result = 0;

  auto m = nums1.size();
  auto n = nums2.size();

  if ((n % 2) != 0) {
    // nums1 contributions don't cancel out.
    result ^= xor_elements(nums1);
  }

  if ((m % 2) != 0) {
    // nums2 contributions don't cancel out.
    result ^= xor_elements(nums2);
  }

  return result;
}