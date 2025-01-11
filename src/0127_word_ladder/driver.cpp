#include "solution.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  // Test Case 1
  std::string beginWord = "hit";
  std::string endWord = "cog";
  std::vector<std::string> wordList;
  wordList.push_back("hot");
  wordList.push_back("dot");
  wordList.push_back("dog");
  wordList.push_back("log");
  wordList.push_back("lot");
  wordList.push_back("cog");
  Solution s;
  auto res = s.ladderLength(beginWord, endWord, wordList);
  std::cout << res << "\n";

  // Test Case 2
  wordList.clear();
  wordList.push_back("hot");
  wordList.push_back("dot");
  wordList.push_back("dog");
  wordList.push_back("log");
  wordList.push_back("lot");
  res = s.ladderLength(beginWord, endWord, wordList);
  std::cout << res << "\n";

  // Test case 3

  beginWord = "red";
  endWord = "tax";
  wordList.clear();
  wordList.push_back("ted");
  wordList.push_back("tex");
  wordList.push_back("red");
  wordList.push_back("tax");
  wordList.push_back("tad");
  wordList.push_back("den");
  wordList.push_back("rex");
  wordList.push_back("pee");
  res = s.ladderLength(beginWord, endWord, wordList);
  std::cout << res << "\n";

  return 0;
}