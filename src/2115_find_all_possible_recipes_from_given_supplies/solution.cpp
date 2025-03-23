#include "solution.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

/**
This problem involves performing a topological sort on the dependency graph of
ingredients to recipes. Consider a recipe `r` with ingredients `i1, i2, ...,
in`. One can think of this ingredient list as a set of directed edges from the
nodes `i1, i2, ..., in` to `r`, creating a directed graph. If one constructs a
graph with all recipes and ingredients list, we will end up with a single, not
necessarily acyclic directed graph. The starting `supplies` list corresponds to
the set of "start nodes" for the graph, i.e., nodes that have no incoming edges.

We can then apply Kahn's algorithm to topologically sort the recipes. Any recipe
that ends up in the topological sorting can be created, and those that remain
after the topological sort cannot. Note that if a recipe includes a base
ingredient that is not in supplies, it will not be incldued in the topological
sort, as Kahn's algorithm only inserts a node to the sort if and only if there
are no incoming edges. Likewise, if two recipes depend upon one another, they
will not end up in the sort, as there are edges from each node to the other.

For Kahn's algorithm, we really only care about the number of "in" nodes to any
given recipe, not the nodes themselves. Thus, we can store only the degree of in
edges for a given recipe to improve efficiency.
*/
std::vector<std::string>
Solution::run(std::vector<std::string> &recipes,
              std::vector<std::vector<std::string>> &ingredients,
              std::vector<std::string> &supplies) {
  // Construct adjacency lists.
  std::unordered_map<std::string, int> in_degrees;
  std::unordered_map<std::string, std::vector<std::string>> out_list;
  for (auto i = 0; i < recipes.size(); ++i) {
    for (auto ingredient : ingredients[i]) {
      out_list[ingredient].push_back(recipes[i]);
    }
    in_degrees[recipes[i]] = ingredients[i].size();
  }

  // Init Kahn's algorithm. Starting nodes are exactly `supplies`. Copy so we
  // don't modify inputs.
  auto supply_lookup =
      std::unordered_set<std::string>{supplies.begin(), supplies.end()};

  auto start_set = supplies;
  std::vector<std::string> sorted_recipes;
  while (!start_set.empty()) {
    auto current = start_set.back();
    start_set.pop_back();
    // NOTE: We do not add supplies to our recipe list, this is a slight
    // divergence from Kahn's algorithm.
    if (!supply_lookup.contains(current)) {
      sorted_recipes.push_back(current);
    }

    for (const auto &recipe : out_list[current]) {
      // Remove current from the recipe's adjacency list. If that is the last
      // edge, we add recipe to our list of start nodes.
      in_degrees[recipe]--;
      if (in_degrees[recipe] == 0) {
        start_set.push_back(recipe);
      }
    }
  }
  return sorted_recipes;
}
