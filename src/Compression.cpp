#include "Compression.hpp"
#include "HuffmanTree.hpp"

static std::string
convertToStringOfBits(const std::string &text,
                                   const std::vector<std::string> &codes) {
  std::string result = "";
  for (const auto &t : text) {
    result += codes[t];
  }
  return result;
}

static std::string convertToStringOfBits(const std::string &text) {
  std::string result = "";
  for (char c : text) {
    std::string temp = "";
    for (int i = 0; i < 8; i++) {
      temp += (c & 1) + '0';
      c >>= 1;
    }
    result += temp;
  }
  return result;
}

static char toChar(const std::string &bits) {
  char ch = 0;
  for (int i = 7; i >= 0; i--) {
    ch |= bool(bits[i] - '0') << i;
  }
  return ch;
}

static std::string toBits(const std::string &text_bits) {
  std::string result;
  for (size_t i = 0; i < text_bits.size() - 8; i += 8) {
    result += toChar(text_bits.substr(i, 8));
  }
  return result;
}

std::string Compression::compress(const std::string &text,
                                  const std::vector<std::string> &code_map) {
  std::string str_bits = convertToStringOfBits(text, code_map);
  std::string result = toBits(str_bits);
  return result;
}

std::string Compression::compineCodeMap(const std::vector<std::string> &codes) {
  std::string map_string;
  for (int i = 0; i < 256; i++)
    map_string += codes[i] + ";";
  return map_string;
}

std::vector<std::string>
Compression::splitCompressedText(const std::string &text) {
  std::vector<std::string> maps(257);
  int start = 0;
  for(int i = 0; i < maps.size() - 1; i++) {
    int end = text.find(';', start);
    maps[i] = text.substr(start, end - start);
    start = end + 1;
  }
  maps.back() = text.substr(start);
  return maps;
}

std::string Compression::decompress(const std::string &text,
                                    const std::vector<std::string> &code_map) {
  auto tree = std::static_pointer_cast<HuffmanTree::HuffInternalNode>(
      HuffmanTree::buildHuffTree(code_map));
  std::string text_bits = convertToStringOfBits(text);
  std::string uncompressed;
  int index = 0;
  while (index != text_bits.size()) {
    auto result = HuffmanTree::findFirst(text_bits, tree, index + 1);
    uncompressed += result.first;
    index = result.second;
  }
  return uncompressed;
}
