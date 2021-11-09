#include <chrono>
#include <gtest/gtest.h>
#include <iostream>

extern "C" {
#include "parallel.h"
#include "standard.h"
}

TEST(isKey, test) {
  char c = '\n';
  char str[] = "abcd\t\nabcd";
  EXPECT_EQ(isKey(c, str), 1);
  c = ' ';
  EXPECT_EQ(isKey(c, str), 0);
}

TEST(filesize, test1) {
  FILE *file;
  file = fopen("../src/test/filesize_test0.txt", "r");
  EXPECT_EQ(filesize(file), 0);
  fclose(file);
  file = fopen("../src/test/filesize_test1.txt", "r");
  EXPECT_EQ(filesize(file), 515);
  fclose(file);
}

TEST(boarders, test1) {
  char str[] = "abc abcdabc ancd anc";
  char keys[] = " ,.!?\n\t";
  int *boarders = getBoarders(str, keys, 4);
  EXPECT_EQ(boarders[1], 11);
}

TEST(standard, test1) {
  char name[] = "../src/test/text.txt";
  char *str = readtext(name);
  int len = maxLenStandard(str);
  EXPECT_EQ(len, 7);
}

TEST(parallel, test1) {
  char name[] = "../src/test/text.txt";
  char *str = readtext(name);
  int len = maxLen(str);
  EXPECT_EQ(len, 7);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
