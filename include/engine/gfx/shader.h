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

// UNIFORMs
// sets boolean uniform
void setBoolean(const int programID, const char* name, bool value);
// sets float uniform
void setFloat(const int programID, const char* name, float value);
// sets integer uniform
void setInteger(const int programID, const char* name, int value);
// sets float vector 2 uniform
void setFloat2(const int programID, const char* name, float value[2]);
// sets int vector 2 uniform
void setInteger2(const int programID, const char* name, int value[2]);
// sets float vector 3 uniform
void setFloat3(const int programID, const char* name, float value[3]);
// sets int vector 3 uniform
void setInteger3(const int programID, const char* name, int value[3]);
// sets float vector 4 uniform
void setFloat4(const int programID, const char* name, float value[4]);
// sets int vector 4 uniform
void setInteger4(const int programID, const char* name, int value[4]);

#endif