#include "standard.h"

int maxLen(char* str) {
    int size = strlen(str);
    char* keys = " \n";
    int maxLength = -1;

    int Length = 0;
    for (int i = 0; i < size; ++i) {
        if (!isKey(str[i], keys)) {
            Length++;
        }
        if (isKey(str[i], keys)) {
            if (Length > maxLength) maxLength = Length;
            Length = 0;
        }
    }

    if (Length > maxLength) maxLength = Length;

    return maxLength;
}