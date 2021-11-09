#include <chrono>
#include <gtest/gtest.h>
#include <iostream>

extern "C" {
#include "parallel.h"
#include "standard.h"
}

TEST(parallel_time, test1) {
  char name[] = "../src/test/big.txt";
  char *str = readtext(name);
  auto start = std::chrono::high_resolution_clock::now();

  maxLen(str);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << std::endl;
  std::cout << "Parallel running time: " << duration.count() << " ms"
            << std::endl;
  std::cout << std::endl;
}

TEST(standard_time, test1) {
  char name[] = "../src/test/big.txt";
  char *str = readtext(name);
  auto start = std::chrono::high_resolution_clock::now();

  maxLenStandard(str);
  clearText(str);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << std::endl;
  std::cout << "Standard running time: " << duration.count() << " ms"
            << std::endl;
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
