#include "parallel.h"

int* getBoarders(char* str, char* keys, int process_count) {
    
    int size = strlen(str);
    printf("str: %s\n", str);

    int* boarders = mmap(NULL, (process_count + 1) * sizeof(int), PROT_READ | PROT_WRITE,
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

int maxLen(char* str) {

    int size = strlen(str);

    char* keys = " ,.!?\n\t";

    int* boarders = getBoarders(str, keys, PRC_CNT);

    int* result = mmap(NULL, PRC_CNT * sizeof(int), PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);


    pid_t* pid = mmap(NULL, PRC_CNT * sizeof(pid_t), PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for (int i = 0; i < PRC_CNT; ++i) { // 4 - количество процессов

        pid[i] = fork();

        if (pid[i] == -1) {
            if (munmap(result, PRC_CNT * sizeof(int)) ||
                munmap(boarders, (PRC_CNT + 1) * sizeof(int)) || 
                munmap(str, size + 1) ||
                munmap(pid, PRC_CNT * sizeof(pid_t))) {

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

    if (munmap(result, PRC_CNT * sizeof(int)) ||
        munmap(boarders, (PRC_CNT + 1) * sizeof(int)) || 
        munmap(str, size + 1)) {
        
        printf("Failed to unmap\n");
        return -1;
    }

    return maxLength;
}