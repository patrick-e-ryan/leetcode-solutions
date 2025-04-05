#include "solution.h"
#include <utility>

typedef std::pair<TreeNode *, int> node_and_depth;

static node_and_depth postorder_traverse(const node_and_depth &root) {
  // Base case, return null and our current depth.
  if (!root.first) {
    return root;
  }

  // Traverse both left and right subtrees, getting their results.
  auto left_result = postorder_traverse({root.first->left, root.second + 1});
  auto right_result = postorder_traverse({root.first->right, root.second + 1});

  if (left_result.second == right_result.second) {
    // We are the LCA (So far). Return the *propogated* depth, not our depth.
    return {root.first, left_result.second};
  } else if (left_result.second > right_result.second) {
    // Left subtree is deeper.
    return left_result;
  } else {
    return right_result;
  }
}

/**
We can perform a typical postorder traversal of the tree, recording our
depth as we go down the left and right subtrees recursively. If the depth of
both the left and right are the same, then we are necessarily the least common
ancestor (LCA) for the deepest leaf nodes, as both the left and the right are
equally deep. Note however that further up the recusion stack a parent of us
could be the true LCA, as it's other subtrees depth could be equal to our depth.

Without loss of generality assume the left child is deeper than the right. Then,
the LCA must be located somewhere in the left subtree, so we propogate the left
tree's result upward. Again, some node further up the recursion stack could be
the true LCA, so the global result is only known once the entire postorder
traversal is complete. See implementation above.
*/
TreeNode *Solution::run(TreeNode *root) {
  auto res = postorder_traverse({root, 0});
  return res.first;
}
