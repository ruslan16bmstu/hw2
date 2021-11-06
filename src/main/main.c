#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "mylib.h"

/*int filesize( FILE *fp ) //Размер файла
{
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
    
    while( (c = fgetc(file)) != EOF ) { // переписать через for
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

int lenWord(char* str) {
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

int* getBoarders(char* str, char* keys, int process_count) {

    int size = strlen(str);

    int* boarders = mmap(NULL, process_count * sizeof(int), PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (!boarders) {
        return NULL;
    }

    boarders[0] = 0;
    boarders[process_count] = size;
    for (int i = 1; i < process_count; ++i) {
        char* p;
        if ( p = strpbrk(str + i * (size / process_count), keys) ) {
            boarders[i] = p - str;
        }
        else {
            boarders[i] = boarders[i - 1];
        }
    }
    return boarders;
}

int maxLenPar(char* str) {

    int size = strlen(str);

    char* keys = " \n";

    int* boarders = getBoarders(str, keys, PRC_CNT);

    int* result = mmap(NULL, PRC_CNT * sizeof(int), PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);


    pid_t* pid = mmap(NULL, PRC_CNT * sizeof(pid_t), PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for (int i = 0; i < PRC_CNT; ++i) { // 4 - количество процессов

        pid[i] = fork();

        if (pid[i] == -1) {
            if(munmap(result, PRC_CNT + 1) || munmap(boarders, PRC_CNT) || munmap(str, size)){
                printf("Failed to unmap\n");
                return -1;
            }
            return -1;
        }

        if (pid[i] == 0) {

            int locMaxLength = -1;

            if (boarders[i] != -1 && boarders[i + 1] != -1) {
                
                int Length = 0;
                for (int j = boarders[i]; j < boarders[i + 1]; ++j) {
                    if (!isKey(str[j], keys)) {
                        Length++;
                    }
                    if (isKey(str[j], keys)) {
                        if (Length > locMaxLength) locMaxLength = Length;
                        Length = 0;
                    }
                }

                if (Length > locMaxLength) locMaxLength = Length;
            }

            result[i] = locMaxLength;

            exit(0);
        }
    }

    for (int i = 0; i < PRC_CNT; ++i) {
        int status;
        waitpid(pid[i], &status, 0);
    }

    if (munmap(pid, PRC_CNT)) {
        printf("Failed to unmap\n");
        return -1;
    }

    int maxLength = -1;

    for (int i = 0; i < PRC_CNT; ++i) {
        //printf("%d\n", result[i]);
        if (result[i] > maxLength) maxLength = result[i];
    }

    if (munmap(result, PRC_CNT + 1) || munmap(boarders, PRC_CNT) || munmap(str, size)) {
        printf("Failed to unmap\n");
        return -1;
    }

    return maxLength;
}*/

int main(int argc, char* argv[]) {
    char* name = "text.txt";
    char* str = readtext(name);

    printf("%d\n", maxLenPar(str));

    return 0;
}