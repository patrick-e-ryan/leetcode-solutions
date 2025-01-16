#include "solution.h"

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <utility>

/**
This problem boils down to finding all shortest-paths in an undirected graph
from a source to a sink. We can break this problem down into two parts:
1. Building the graph
2. Fully traversing the graph.

This code is based on the solution to the more challenging 0126, which requires
a different approach to BFS.
*/
int Solution::ladderLength(std::string beginWord, std::string endWord,
                           std::vector<std::string> &wordList) {
  // Shortcut: If endWord is not in wordList, there is no solution.
  if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
    return 0;
  }

  // Add our first word to the word list if not present.
  if (std::find(wordList.begin(), wordList.end(), beginWord) ==
      wordList.end()) {
    wordList.push_back(beginWord);
  }

  // Build our graph using an adjacency list.
  // First, create our lookup / marking table to keep track of what verticies
  // have been visited.
  typedef bool lookup_value;
  std::unordered_map<std::string, lookup_value> search_set;
  for (auto i = 0; i < wordList.size(); ++i) {
    const auto &word = wordList[i];
    search_set[word] = false;
  }

  // We label each word in wordList by the word itself.
  std::unordered_map<std::string, std::vector<std::string>> adjacency_list;
  for (const auto &word : wordList) {
    std::vector<std::string> neighbors;
    for (int letter = 0; letter < word.size(); ++letter) {
      for (char c = 'a'; c <= 'z'; ++c) {
        auto tmp = word;
        tmp[letter] = c;
        if (search_set.contains(tmp) && tmp != word &&
            !(std::find(neighbors.begin(), neighbors.end(), tmp) !=
              neighbors.end())) { // Don't include ourselves, or duplicates.
          neighbors.push_back(tmp);
        }
      }
    }
    adjacency_list[word] = std::move(neighbors);
  }

  // Now, we explore the graph via BFS.
  typedef std::pair<std::string, std::vector<std::string>>
      queue_value_type; // vertex, search path.
  std::queue<queue_value_type> queue;
  queue.push({beginWord, {}});

  std::vector<std::vector<std::string>> paths;
  while (!queue.empty()) {
    // Pop top and mark visited. Then, enqueue all non-visited neighbors.
    auto queue_pair = queue.front(); // Note, this is a copy.
    auto current = queue_pair.first;
    auto current_path = queue_pair.second; // copy

    current_path.push_back(current);
    queue.pop();
    if (search_set[current]) {
      // We've already visited this node. Add ourselves to it's
      continue;
    }

    search_set[current] = true;
    for (const auto &neighbor : adjacency_list[current]) {
      // If we hit the end node, don't enqueue anything. Save off our current
      // path and continue iterating.
      if (std::find(adjacency_list[current].begin(),
                    adjacency_list[current].end(),
                    endWord) != adjacency_list[current].end()) {
        current_path.push_back(endWord);
        paths.push_back(current_path);

        // Clear queue and terminate.
        while (!queue.empty()) {
          queue.pop();
        }
        break;
      }

      if (!search_set[neighbor]) {
        // We're not visited. Enqueue.
        queue.push({neighbor, current_path});
      }
    }
  }
  if (paths.size() > 0) {
    return paths[0].size();
  }
  return 0;
}
