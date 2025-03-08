#include "solution.h"

#include <algorithm>

/**
This problem boils down to propagating constraints through the vector, and
determining if there are any contradictions discovered along the way. This will
take, at worst O(n) time, as one must generically propogate all constraints to
confirm validity, and O(1) space to compute.

The boundary constraint that derived[n-1] = original[n-1] ^ original[0] is the
sole decider on validity, as this imposes a second constraint on original[0]:

derived[0] = original[0] ^ original[1]
derived[n-1] = original[n-1] ^ original[0]

The values of derived[i] correspond to whether original[i] == original[i+1], due
to the nature of the XOR operation. Hence,

derived[i] == 1 ==> original[i] != origianl[i + 1], otherwise
derived[i] == 0 ==> original[i] == original[i+1]

This lets us simply accumulate the "current value" of what the `original` vector
should be, and propogate the constraints forward. All one needs to check in the
end is that the "current value" after propogation matches the boundary
constraint. Further, setting our initial value to 1 (which is possible due to
symmetry of the XOR operation) we simply need to check that the propogated
constraint is also ture.
*/
bool Solution::run(std::vector<int> derived) {
  using std::ranges::fold_left;
  auto propogate_constraint = [](bool val, int swap) {
    return swap ? !val : val;
  };

  int constrained_result = fold_left(derived, true, propogate_constraint);
  return constrained_result;
}

/**
Illustrative example with O(n) space complexity.
*/
static bool run_slow(std::vector<int> derived) {
  std::vector<int> original(derived.size());

  original[0] = 0;
  for (auto i = 0; i < derived.size(); ++i) {
    if (i == derived.size() - 1) {
      // Terminating condition, we determine validity here.
      if (derived[i]) {
        return original[i] != original[0];
      }
      return original[i] == original[0];
    }
    if (derived[i]) {
      // original[i] != original[i + 1]
      original[i + 1] = !original[i];
    } else {
      // original[i] == original[i + 1]
      original[i + 1] = original[i];
    }
  }
  // Should not reach.
  return false;
}
