#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "mylib.h"
#include "parallel.h"

int main(int argc, char* argv[]) {
    char* name = "../text.txt";
    char* str = readtext(name);
    printf("Parallel program\n");
    printf("The maximum word length in the text.txt: %d\n", maxLen(str));
    return 0;
}
