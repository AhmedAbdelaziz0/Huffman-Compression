#include "HuffmanTree.hpp"
#include "UserInputHandler.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

std::vector<int> countCharacters(const std::string &str) {
  std::vector<int> counts(256, 0);
  for (const auto &ch : str) {
    counts[ch]++;
  }
  return counts;
}

HuffmanTree::PriorityQueue makeQueue(const std::vector<int> &counts) {
  HuffmanTree::PriorityQueue queue;
  for (int i = 0; i < counts.size(); i++) {
    if (counts[i] > 0) {
      queue.push(std::shared_ptr<HuffmanTree::HuffNode>(
          new HuffmanTree::HuffLeafNode(counts[i], i)));
    }
  }
  return queue;
}

template <typename T> void Log(const std::vector<T> &vec) {
  for (const auto &v : vec) {
    std::cout << v << ", ";
  }
  std::cout << '\n';
}

void Log(const std::string &str) { std::cout << str << std::endl; }

// TODO get from command line
// TODO write function or class for the input from command line ( getFileFromUser )
int main() {
  std::ifstream text_file = UserInputHandler::getFileFromUser();
  std::string text = UserInputHandler::toString(text_file);
  text.pop_back();

  std::vector<int> occurrence = countCharacters(text);
  auto queue = makeQueue(occurrence);
  auto huff_tree = HuffmanTree::buildHuffTree(queue);
  std::string temp;
  std::vector<std::pair<char, std::string>> codes;
  HuffmanTree::GetPrefixTable(huff_tree, temp, codes);
  for(auto c: codes) {
    std::cout << c.first << " " << c.second << std::endl;
  }

  return 0;
}
