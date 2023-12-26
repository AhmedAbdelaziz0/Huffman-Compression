#include "PrefixCode.hpp"
#include <gtest/gtest.h>

TEST(count_characters, empty_list) {
  std::string in = "";
  std::vector<int> out(256, 0);
  auto result = PrefixCode::countCharacters(in);
  ASSERT_EQ(result, out);
}

TEST(count_characters, single_char) {
  std::string in = "a";
  std::vector<int> out(256, 0);
  out['a'] = 1;
  auto result = PrefixCode::countCharacters(in);
  ASSERT_EQ(result, out);
}

TEST(count_characters, multiple_chars_of_same_char) {
  std::string in = "bbbbb";
  std::vector<int> out(256, 0);
  out['b'] = 5;
  auto result = PrefixCode::countCharacters(in);
  ASSERT_EQ(result, out);
}

TEST(count_characters, different_chars) {
  std::string in = "abcdef";
  std::vector<int> out(256, 0);
  out['a'] = 1;
  out['b'] = 1;
  out['c'] = 1;
  out['d'] = 1;
  out['e'] = 1;
  out['f'] = 1;
  auto result = PrefixCode::countCharacters(in);
  ASSERT_EQ(result, out);
}

TEST(count_characters, general_test) {
  std::string in = "cda: bdda abc ddd\n";
  std::vector<int> out(256, 0);
  out['a'] = 3;
  out['b'] = 2;
  out['c'] = 2;
  out['d'] = 6;
  out[':'] = 1;
  out['\n'] = 1;
  out[' '] = 3;
  auto result = PrefixCode::countCharacters(in);
  ASSERT_EQ(result, out);
}
