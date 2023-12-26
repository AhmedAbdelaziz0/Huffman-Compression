#include "PrefixCode.hpp"
#include "HuffmanTree.hpp"

std::vector<int> PrefixCode::countCharacters(const std::string &str) {
  std::vector<int> counts(256, 0);
  for (const auto &ch : str) {
    counts[ch]++;
  }
  return counts;
}

HuffmanTree::PriorityQueue PrefixCode::makeQueue(const std::vector<int> &counts) {
  HuffmanTree::PriorityQueue queue;
  for (int i = 0; i < counts.size(); i++) {
    if (counts[i] > 0) {
      queue.push(std::shared_ptr<HuffmanTree::HuffNode>(
          new HuffmanTree::HuffLeafNode(counts[i], i)));
    }
  }
  return queue;
}

std::vector<std::string> PrefixCode::getCodePrefix(const std::string &text) {
  std::vector<int> occurrence = countCharacters(text);
  auto queue = makeQueue(occurrence);
  auto huff_tree = HuffmanTree::buildHuffTree(queue);
  std::string holder;
  std::vector<std::string> codes(256);
  HuffmanTree::GetPrefixTable(huff_tree, holder, codes);
  return codes;
}
