#include "HuffmanTree.hpp"
#include <iostream>
#include <memory>
#include <string>

HuffmanTree::HuffLeafNode::HuffLeafNode(int weight, char element) {
  this->element = element;
  this->weight = weight;
  type = LEAF;
}

const char HuffmanTree::HuffLeafNode::value() const { return element; }

HuffmanTree::HuffInternalNode::HuffInternalNode() {
  left = nullptr;
  right = nullptr;
}

void HuffmanTree::HuffInternalNode::Left(
    std::shared_ptr<HuffmanTree::HuffNode> node) {
  left = node;
}

void HuffmanTree::HuffInternalNode::Right(
    std::shared_ptr<HuffmanTree::HuffNode> node) {
  right = node;
}

HuffmanTree::HuffInternalNode::HuffInternalNode(std::shared_ptr<HuffNode> l,
                                                std::shared_ptr<HuffNode> r) {
  this->weight = l->weight + r->weight;
  this->left = l;
  this->right = r;
  type = INTERNAL;
}
std::shared_ptr<HuffmanTree::HuffNode>
HuffmanTree::HuffInternalNode::Left() const {
  return left;
}
std::shared_ptr<HuffmanTree::HuffNode>
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

inline static bool hasValue(const std::string &str) { return !str.empty(); }

inline static std::shared_ptr<HuffmanTree::HuffInternalNode>
getChild(const std::shared_ptr<HuffmanTree::HuffNode> &child) {
  if (child == nullptr)
    return std::shared_ptr<HuffmanTree::HuffInternalNode>(
        (new HuffmanTree::HuffInternalNode));
  else
    return std::static_pointer_cast<HuffmanTree::HuffInternalNode>(child);
}

inline static std::shared_ptr<HuffmanTree::HuffInternalNode>
constructPath(std::shared_ptr<HuffmanTree::HuffInternalNode> current,
              const std::string &code) {
  std::shared_ptr<HuffmanTree::HuffInternalNode> child;
  for (int j = 0; j < code.size() - 1; j++) {
    if (code[j] == '0') {
      child = getChild(current->Left());
      current->Left(child);
    } else {
      child = getChild(current->Right());
      current->Right(child);
    }
    current = child;
  }
  return current;
}

inline static void
constructLeaf(std::shared_ptr<HuffmanTree::HuffInternalNode> leafParent, char c,
              bool isLeft) {
  auto leaf = std::shared_ptr<HuffmanTree::HuffLeafNode>(
      (new HuffmanTree::HuffLeafNode(0, c)));
  if (isLeft) {
    leafParent->Left(leaf);
  } else {
    leafParent->Right(leaf);
  }
}

std::shared_ptr<HuffmanTree::HuffNode>
HuffmanTree::buildHuffTree(const std::vector<std::string> &code_map) {
  std::shared_ptr<HuffInternalNode> head(new HuffInternalNode);
  std::shared_ptr<HuffInternalNode> current = head;
  for (int i = 0; i < 256; i++) {
    current = head;
    if (hasValue(code_map[i])) {
      auto leafParent = constructPath(head, code_map[i]);
      constructLeaf(leafParent, char(i), code_map[i].back() == '0');
    }
  }
  return head;
}

std::pair<char, int>
HuffmanTree::findFirst(const std::string &bits,
                       std::shared_ptr<HuffInternalNode> current, int start) {
  for (int i = start; i < bits.size(); i++) {
    bool isLeft = bits[i] == '0';
    current = std::static_pointer_cast<HuffInternalNode>(
        isLeft ? current->Left() : current->Right());
    if (current->type == LEAF) {
      auto leaf = std::static_pointer_cast<HuffLeafNode>(
          std::static_pointer_cast<HuffNode>(current));
      return std::make_pair(leaf->value(), i);
    }
  }
  return std::make_pair('\n', bits.size());
}

void HuffmanTree::GetPrefixTable(std::shared_ptr<HuffmanTree::HuffNode> tree,
                                 std::string code,
                                 std::vector<std::string> &codes) {
  if (tree->type == INTERNAL) {
    std::shared_ptr<HuffInternalNode> node =
        std::static_pointer_cast<HuffInternalNode>(tree);
    GetPrefixTable(node->Left(), code + '0', codes);
    GetPrefixTable(node->Right(), code + '1', codes);
  } else if (tree->type == LEAF) {
    auto node = std::static_pointer_cast<HuffLeafNode>(tree);
    codes[node->value()] = code;
  }
}
