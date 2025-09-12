/*
FILE:
File reader/writer
*/

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdbool.h>

// returns the file pointer corresponding to the file at the given path ("./file" means it is in "g3ce")
FILE* file_open(char* path, char* mode);

// writes content to a file at path ("./file" means it is in "g3ce")
bool file_write(char* path, char* content);
// reads a file at path and outputs its content to content ("./file" means it is in "g3ce")
// YOU MUST FREE THE RETURN VALUE!
char* file_read(char* path);
// removes a file at path ("./file" means it is in "g3ce")
int file_remove(char* path);

#endif