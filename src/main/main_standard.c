#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mylib.h"
#include "standard.h"

int main(int argc, char *argv[]) {
  char *name = "../src/test/words.txt";
  char *str = readtext(name);
  printf("Standard program\n");
  printf("The maximum word length in the text.txt: %d\n", maxLenStandard(str));
  clearText(str);
  return 0;
}
