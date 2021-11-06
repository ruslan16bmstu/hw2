#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

int filesize( FILE *fp );

char* readtext(char* fname);

int isKey(char symbol, char* keys);