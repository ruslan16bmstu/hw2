#include "mylib.h"

int filesize( FILE *fp ) {//Размер файла
    int size_of_file;
    fseek( fp, 0, SEEK_END );
    size_of_file = ftell( fp );
    fseek( fp, 0, SEEK_SET );
    return( size_of_file );
}

char* readtext(char* fname) {
    FILE *file;
    file = fopen(fname, "r");

    char c;
    int counter = 0;
    int size = filesize(file);

    char *text = mmap(NULL, size, PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    while( (c = fgetc(file)) != EOF ) {
        text[counter++] = c;
    }

    text[size] = '\0';

    fclose(file);
    return text;
}

int isKey(char symbol, char* keys) {
    for (int i = 0; i < strlen(keys); ++i) {
        if (symbol == keys[i]) return 1;
    }
    return 0;
}