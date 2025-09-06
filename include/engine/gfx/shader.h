/*
SHADER:
Shader handler
*/

#ifndef SHADER_H
#define SHADER_H

// creates a shader from a file path ("./file" means it is in "g3ge")
int shader_get(char* path, int type);

// creates a shader program from the given vertex and fragment shader codes ("./file" means it is in "g3ge")
int shader_create(char* vertexPath, char* fragmentPath);
// uses the given shader
void shader_use(int programID);
// destroys the given shader
void shader_destroy(int programID);

#endif