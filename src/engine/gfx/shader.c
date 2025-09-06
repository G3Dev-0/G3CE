/*
SHADER:
Shader handler
*/

#include <stdlib.h>

#include <glad/glad.h>

#include "engine/utils/file.h"
#include "engine/utils/console.h"

#include "engine/gfx/shader.h"

// creates a shader from a file path ("./file" means it is in "g3ge")
int shader_get(char* path, int type) {
    const char* source = file_read(path);
    if (source == NULL) return -1;

    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    
    free(source); // FREE THE RETURN VALUE OF file_read(path);
    
    glCompileShader(id);

    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        console_error("Failed to compile shader at \"%s\"\nCompilation produced the following error:", path);
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        console_output("%s%s", COLOR_RED, infoLog);
        return -1;
    }

    return id;
}

// creates a shader program from the given vertex and fragment shader codes ("./file" means it is in "g3ge")
int shader_create(char* vertexPath, char* fragmentPath) {
    int vertexID = shader_get(vertexPath, GL_VERTEX_SHADER);
    int fragmentID = shader_get(fragmentPath, GL_FRAGMENT_SHADER);

    if (vertexID == -1 || fragmentID == -1) {
        console_error("Could not create shader program with shaders at \"%s\" (vertex) \"%s\" (fragment)", vertexPath, fragmentPath);
        return -1;
    }

    // create program
    int programID = glCreateProgram();
    // attach the vertex and fragment shaders
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    // link the program
    glLinkProgram(programID);

    // free memory now, it's not needed to have the indipendent shaders still allocated after attaching and linking them to the program
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    return programID;
}

// uses the given shader
void shader_use(int programID) {
    glUseProgram(programID);
}

// destroys the given shader
void shader_destroy(int programID) {
    glDeleteProgram(programID);
}