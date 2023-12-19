#include "HuffmanTree.hpp"
#include <memory>
#include <string>

HuffmanTree::HuffLeafNode::HuffLeafNode(int weight, char element) {
  this->element = element;
  this->weight = weight;
  type = LEAF;
}
const char HuffmanTree::HuffLeafNode::value() const { return element; }

HuffmanTree::HuffInternalNode::HuffInternalNode(std::shared_ptr<HuffNode> l,
                                                std::shared_ptr<HuffNode> r) {
  this->weight = l->weight + r->weight;
  this->left = l;
  this->right = r;
  type = INTERNAL;
}
const std::shared_ptr<HuffmanTree::HuffNode>
HuffmanTree::HuffInternalNode::Left() const {
  return left;
}
const std::shared_ptr<HuffmanTree::HuffNode>
HuffmanTree::HuffInternalNode::Right() const {
  return right;
}

std::shared_ptr<HuffmanTree::HuffNode>
HuffmanTree::buildHuffTree(PriorityQueue queue) {
  while (queue.size() > 1) {
    auto node1 = queue.top();
    queue.pop();

    auto node2 = queue.top();
    queue.pop();

    std::shared_ptr<HuffNode> node(new HuffInternalNode(node1, node2));
    queue.push(node);
  }
  return queue.top();
}

void HuffmanTree::GetPrefixTable(
    std::shared_ptr<HuffmanTree::HuffNode> tree, std::string code,
    std::vector<std::pair<char, std::string>> &codes) {
  if (tree->type == INTERNAL) {
    std::shared_ptr<HuffInternalNode> node =
        std::static_pointer_cast<HuffInternalNode>(tree);
    GetPrefixTable(node->Left(), code + '0', codes);
    GetPrefixTable(node->Right(), code + '1', codes);
  } else if (tree->type == LEAF) {
    auto node = std::static_pointer_cast<HuffLeafNode>(tree);
    codes.emplace_back(std::make_pair(node->value(), code));
  }
}
