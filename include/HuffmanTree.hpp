#pragma once

#include <memory>
#include <queue>
#include <string>

namespace HuffmanTree {
enum TYPE { LEAF, INTERNAL };

class HuffNode {
public:
  int weight;
  TYPE type;
};

class HuffLeafNode : public HuffNode {
private:
  char element;

public:
  HuffLeafNode(int weight, char element);
  const char value() const;
};

class HuffInternalNode : public HuffNode {
private:
  std::shared_ptr<HuffNode> left;
  std::shared_ptr<HuffNode> right;

public:
  HuffInternalNode();

  void Left(std::shared_ptr<HuffmanTree::HuffNode> node);

  void Right(std::shared_ptr<HuffmanTree::HuffNode> node);

  HuffInternalNode(std::shared_ptr<HuffNode> l, std::shared_ptr<HuffNode> r);

  std::shared_ptr<HuffNode> Left() const;

  std::shared_ptr<HuffNode> Right() const;
};

class CompareHuffNode {
public:
  bool operator()(std::shared_ptr<HuffNode> h1,
                  std::shared_ptr<HuffNode> h2) const {
    return h1->weight > h2->weight;
  }
};

using PriorityQueue =
    std::priority_queue<std::shared_ptr<HuffNode>,
                        std::vector<std::shared_ptr<HuffNode>>,
                        CompareHuffNode>;

std::shared_ptr<HuffmanTree::HuffNode> buildHuffTree(PriorityQueue queue);

std::shared_ptr<HuffmanTree::HuffNode>
buildHuffTree(const std::vector<std::string> &code_map);

std::pair<char, int> findFirst(const std::string &bits,
                               std::shared_ptr<HuffInternalNode> head,
                               int start);

void GetPrefixTable(std::shared_ptr<HuffmanTree::HuffNode> tree,
                    std::string code, std::vector<std::string> &codes);

} // namespace HuffmanTree
