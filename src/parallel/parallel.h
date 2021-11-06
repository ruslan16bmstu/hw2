#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mylib.h"

#define PRC_CNT 4

int* getBoarders(char* str, char* keys, int process_count);

int maxLenPar(char* str);
