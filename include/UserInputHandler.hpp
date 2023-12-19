#include <fstream>
#include <string>

enum ERRORS { INVALID_PATH, INVALID_FILE_TYPE };

void printErrorMessage(ERRORS error);

namespace UserInputHandler {
std::ifstream getFileFromUser();
std::string toString(const std::ifstream &file);
} // namespace UserInputHandler
