#include "solution.h"
#include <array>
#include <climits>
#include <deque>
#include <vector>

enum class Direction : int {
  Right = 1,
  Left = 2,
  Down = 3,
  Up = 4,
};

typedef std::pair<int, int> Coordinate; // (y, x)

constexpr inline Coordinate neighbor(const Coordinate &c, Direction direction) {
  switch (direction) {
  case Direction::Right:
    return {c.first, c.second + 1};
  case Direction::Left:
    return {c.first, c.second - 1};
  case Direction::Down:
    return {c.first + 1, c.second};
  case Direction::Up:
    return {c.first - 1, c.second};
  }
}

class Grid {
public:
  Grid(int width, int height) {
    weights_ =
        std::vector<std::vector<int>>(height, std::vector<int>(width, INT_MAX));
    height_ = height;
    width_ = width;
  }

  int at(const Coordinate &c) { return weights_[c.first][c.second]; }

  void set(const Coordinate &c, int val) { weights_[c.first][c.second] = val; }

  constexpr inline bool is_in_bounds(const Coordinate &c) {
    return (c.first >= 0 && c.first < height_) &&
           (c.second >= 0 && c.second < width_);
  }

private:
  std::vector<std::vector<int>> weights_;
  int width_;
  int height_;
};

/**
For a binary (0-1) graph, it is sufficient to use a variant of BFS to
explore the graph for a minimal-weight path. This is due to the fact that
zero-weight edges are "free", not contributing to the overall path weight.
Thus, the only edges that are relevant to the path are those that are
one-weighted, and any one-weighted edges that are transitively connected by
only zero-weight edges may be considered connected. This formulation reduces
precisely to a regular shortest-path traversal problem, leading to our
decision to use BFS.
*/
int Solution::run(std::vector<std::vector<int>> &grid) {
  std::deque<Coordinate> search_queue{};

  // Initialize our costs lookup to have all maximum weights.
  Grid weights(grid.size(), grid[0].size());

  // Prep the state.
  weights.set({0, 0}, 0);
  search_queue.push_front({0, 0});
  const int width = grid.size() - 1;
  const int height = grid[0].size() - 1;
  const Coordinate end = {width, height};
  const std::array<Direction, 4> directions = {
      Direction::Right, Direction::Left, Direction::Down, Direction::Up};

  // Perform BFS, pushing zero-weight edges to the front of the queue, and
  // one-weighted to the end. This guarantees we explore as far as possible
  // for free first.
  while (!search_queue.empty()) {
    Coordinate current = search_queue.front();
    search_queue.pop_front();

    if (current == end) {
      break;
    }

    // Iterate over each direction, assigning the costs in our weight grid for
    // each step.
    for (const auto &direction : directions) {
      auto next = neighbor(current, direction);
      if (weights.is_in_bounds(next)) {
        int cost = direction != Direction{grid[current.first][current.second]};
        // Is this a better path than any previously explored?
        // NOTE: We do not add this edge/path to the search if we already have a
        // cheaper path to the node.
        if (weights.at(current) + cost < weights.at(next)) {
          // Yes, update the cost for this path.
          weights.set(next, weights.at(current) + cost);

          // Append to deque. If this edge is free, use high priority.
          if (!cost) {
            search_queue.push_front(next);
          } else {
            search_queue.push_back(next);
          }
        }
      }
    }
  }

  return weights.at(end);
}
