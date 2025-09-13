/*
SHADER:
Shader handler
*/

#ifndef SHADER_H
#define SHADER_H

// creates a shader program from the given vertex and fragment shader codes ("./file" means it is in "g3ce")
unsigned int shader_create(char* vertexPath, char* fragmentPath);
// destroys the given shader
void shader_destroy(unsigned int programID);

// UNIFORMs
// sets boolean uniform
void shader_setBoolean(const unsigned int programID, const char* name, bool value);
// sets float uniform
void shader_setFloat(const unsigned int programID, const char* name, float value);
// sets integer uniform
void shader_setInteger(const unsigned int programID, const char* name, int value);
// sets float vector 2 uniform
void shader_setFloat2(const unsigned int programID, const char* name, float value[2]);
// sets int vector 2 uniform
void shader_setInteger2(const unsigned int programID, const char* name, int value[2]);
// sets float vector 3 uniform
void shader_setFloat3(const unsigned int programID, const char* name, float value[3]);
// sets int vector 3 uniform
void shader_setInteger3(const unsigned int programID, const char* name, int value[3]);
// sets float vector 4 uniform
void shader_setFloat4(const unsigned int programID, const char* name, float value[4]);
// sets int vector 4 uniform
void shader_setInteger4(const unsigned int programID, const char* name, int value[4]);

#endif