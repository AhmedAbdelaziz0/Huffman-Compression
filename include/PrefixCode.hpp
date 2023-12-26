#pragma once

#include "HuffmanTree.hpp"
#include <string>
#include <vector>

namespace PrefixCode {

std::vector<std::string> getCodePrefix(const std::string &text);
std::vector<int> countCharacters(const std::string &str);
HuffmanTree::PriorityQueue makeQueue(const std::vector<int> &counts);
} // namespace PrefixCode
