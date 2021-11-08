#include <iostream>
#include <gtest/gtest.h>

extern "C" {
    #include "mylib.h"
    #include "parallel.h"

}

TEST(parallel1, test1) {
    char* name = "../text.txt";
    char* str = readtext(name);
    int len = maxLen(str);
    printf("%d\n", len);
    EXPECT_EQ(len, 7);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*TEST(filesize, test) {
    FILE *file;
    file = fopen("../src/test/filesize_test0.txt", "r");
    EXPECT_EQ(filesize(file), 0);
    fclose(file);
    file = fopen("../src/test/filesize_test1.txt", "r");
    EXPECT_EQ(filesize(file), 17);
    fclose(file);
}

TEST(isKey, test) {
    char c = '\n';
    char* str = "abcd\t\nabcd";
    EXPECT_EQ(isKey(c, str), 1);
    c = ' ';
    EXPECT_EQ(isKey(c, str), 0);
}*/

/*TEST(parallel, test) {
    //char* fname = "../src/test/maxLen_test1.txt";
    //char* str = readtext(fname);
    

    char* name = "../text.txt";
    char* str = readtext(name);
    char* text = "abcd";
    printf("%d\n", strlen(str));
    printf("%d\n", strlen(text));
    EXPECT_EQ(strcmp(text, str), 0);
}*/