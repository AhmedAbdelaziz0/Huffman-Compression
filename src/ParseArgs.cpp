#include <ParseArgs.hpp>

Parser::Arguments Parser::parseArguments(int argc, char **argv) {
  Arguments arg;
  arg.input_file = argv[1];
  arg.output_file = argv[2];
  arg.isCompress = !std::string(argv[3]).compare("compress");
  return arg;
}
