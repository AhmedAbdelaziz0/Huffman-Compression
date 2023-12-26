#include "Compression.hpp"
#include "FileHandler.hpp"
#include "ParseArgs.hpp"
#include "PrefixCode.hpp"

int main(int argc, char **argv) {
  Parser::Arguments arguments = Parser::parseArguments(argc, argv);

  if (arguments.isCompress) {
    std::string original_text =
        FileHandler::loadFileAsString(arguments.input_file);
    original_text += char(1);
    std::vector<std::string> code_map =
        PrefixCode::getCodePrefix(original_text);
    std::string compressed = Compression::compress(original_text, code_map);
    std::string compined = Compression::compineCodeMap(code_map);
    FileHandler::saveFile(compined + compressed, arguments.output_file);
  } else {
    std::string compressed_text =
        FileHandler::loadFileAsString(arguments.input_file);
    std::vector<std::string> code_map =
        Compression::splitCompressedText(compressed_text);
    compressed_text = code_map.back();
    code_map.pop_back();
    std::string original_text =
        Compression::decompress(compressed_text, code_map);
    FileHandler::saveFile(original_text, arguments.output_file);
  }

  return 0;
}
