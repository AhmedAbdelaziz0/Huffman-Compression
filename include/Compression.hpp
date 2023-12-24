#pragma once
#include <string>
#include <vector>

namespace Compression {

std::string compress(const std::string &text,
                     const std::vector<std::string> &code_map);

std::string compineCodeMap(const std::vector<std::string> &codes);

std::vector<std::string> splitCompressedText(const std::string &text);

std::string decompress(const std::string &text,
                       const std::vector<std::string> &code_map);
} // namespace Compression
