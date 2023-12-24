#pragma once
#include <string>

namespace FileHandler {
std::string loadFileAsString(const std::string &file_path);
void saveFile(const std::string &text, const std::string &file_path);
} // namespace UserInputHandler
