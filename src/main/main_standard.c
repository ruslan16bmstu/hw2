#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "mylib.h"
#include "standard.h"

int main(int argc, char* argv[]) {
    char* name = "../text.txt";
    char* str = readtext(name);
    printf("Standard program\n");
    printf("The maximum word length in the text.txt: %d\n", maxLenStandard(str));
    return 0;
}
