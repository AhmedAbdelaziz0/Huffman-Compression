#include "FileHandler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static std::ifstream loadFile(const std::string &file_name) {
  std::ifstream file(file_name);
  if (file.good() && file.is_open())
    return file;
  else
    throw "Error happen while openning the file";
}

std::string FileHandler::loadFileAsString(const std::string &file_path) {
  auto file = loadFile(file_path);
  std::stringstream strStream;
  strStream << file.rdbuf();
  file.close();

  std::string str = strStream.str();
  return str;
}

void FileHandler::saveFile(const std::string &text,
                           const std::string &file_path) {
  std::ofstream outputFile(file_path);

  if (outputFile.is_open()) {
    outputFile << text;
    outputFile.close();
    std::cout << "Data was written to " << file_path << std::endl;
  } else {
    std::cerr << "Error opening file\n";
  }
}
