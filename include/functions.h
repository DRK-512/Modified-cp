#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <string.h> // strchr
#include <sys/stat.h> // stat

int init_values(int argc, char** argv, int* nCopies, int* verbose, char** srcPath, char** destPath);
int dir_exists(const char *path);
void split_file(char* srcPath, char** pre_ext, char** post_ext);
int get_num_digits(int num);
void copyFile(const char *old_file, const char *new_file);

#endif