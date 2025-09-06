/*
FILE:
File reader/writer
*/

#include <stdlib.h>
#include <string.h>

#include "engine/utils/console.h"

#include "engine/utils/file.h"

// returns the file pointer corresponding to the file at the given path ("./file" means it is in "g3ge")
FILE* file_open(char* path, char* mode) {
    FILE* file = fopen(path, mode);
    if (file == NULL) {
        console_error("Failed to open file at \"%s\"", path);
        return NULL;
    }
    return file;
}

// writes content to a file at path ("./file" means it is in "g3ge")
bool file_write(char* path, char* content) {
    FILE* file = file_open(path, "w");
    if (file == NULL) return false;
    fputs(content, file);
    fclose(file);
    return true;
}

// reads a file at path and outputs its content to content ("./file" means it is in "g3ge")
// YOU MUST FREE THE RETURN VALUE!
char* file_read(char* path) {
    // open the file
    FILE* file = file_open(path, "r");
    if (file == NULL) return NULL;
    
    // get file length
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // read the file content
    char* buffer = (char*) malloc(length + 1); // +1 for \0
    if (buffer == NULL) {
        fclose(file);
        console_error("Failed to allocate memory for reading buffer of file at \"%s\"", path);
        return NULL;
    }

    // args: buffer wher to output, size of char, length (amount) of the elements, file pointer
    size_t read_bytes = fread(buffer, 1, length, file);
    // check for having read the whole file
    if (read_bytes < length) {
        fclose(file);
        console_error("Failed to read the whole file at \"%s\"", path);
        return NULL;
    }

    // add terminator
    buffer[read_bytes] = '\0';

    fclose(file);

    return buffer;
}

// removes a file at path ("./file" means it is in "g3ge")
int file_remove(char* path) {
    return remove(path);
}