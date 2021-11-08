#include "standard.h"

int maxLenStandard(char *str) {
  int size = strlen(str);
  char *keys = " ,.!?\n\t";
  int maxLength = -1;

  int Length = 0;
  for (int i = 0; i < size; ++i) {
    if (!isKey(str[i], keys)) {
      Length++;
    }
    if (isKey(str[i], keys)) {
      if (Length > maxLength)
        maxLength = Length;
      Length = 0;
    }
  }

  if (Length > maxLength)
    maxLength = Length;

  return maxLength;
}

int clearText(char* str) {
  int size = strlen(str);
  if (munmap(str, size + 1)) {
    printf("Failed to unmap\n");
    return -1;
  }
  return 0;
}
