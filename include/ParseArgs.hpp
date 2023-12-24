#pragma once
#include <string>

namespace Parser {

struct Arguments {
  std::string input_file;
  std::string output_file;
  bool isCompress = true;
};

Arguments parseArguments(int argc, char **argv);
} // namespace Parser
