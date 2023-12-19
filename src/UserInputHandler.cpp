#include "UserInputHandler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void printErrorMessage(ERRORS error) {
  switch (error) {
  case INVALID_PATH:
    break;
  case INVALID_FILE_TYPE:
    break;
  default:
    throw "not implemented";
  };
}

static std::string getUserInput() {
  std::string input;
  std::cout << "Enter a file name: ";
  std::cin >> input;
  return input;
}

static std::ifstream loadFile(const std::string &file_name) {
  std::ifstream file(file_name);
  if (file.good() && file.is_open())
    return file;
  else
    throw "Error happen while openning the file";
}

std::ifstream UserInputHandler::getFileFromUser() {
  std::string input = getUserInput();
  auto text_file = loadFile(input);
  return text_file;
}

std::string UserInputHandler::toString(const std::ifstream &file) {
  std::stringstream strStream;
  strStream << file.rdbuf();
  std::string str = strStream.str();
  return str;
}
