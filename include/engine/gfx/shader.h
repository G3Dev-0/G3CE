/*
SHADER:
Shader handler
*/

#ifndef SHADER_H
#define SHADER_H

#include "engine/math/linal.h"

// creates a shader program from the given vertex and fragment shader codes ("./file" means it is in "g3ce")
unsigned int shader_create(char* vertexPath, char* fragmentPath);
// destroys the given shader
void shader_destroy(unsigned int programID);

// UNIFORMs
// sets boolean uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setBoolean(const unsigned int programID, const char* name, bool value);
// sets float uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setFloat(const unsigned int programID, const char* name, float value);
// sets integer uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setInteger(const unsigned int programID, const char* name, int value);
// sets float vector 2 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setFloat2(const unsigned int programID, const char* name, float value[2]);
// sets int vector 2 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setInteger2(const unsigned int programID, const char* name, int value[2]);
// sets float vector 3 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setFloat3(const unsigned int programID, const char* name, float value[3]);
// sets int vector 3 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setInteger3(const unsigned int programID, const char* name, int value[3]);
// sets float vector 4 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setFloat4(const unsigned int programID, const char* name, float value[4]);
// sets int vector 4 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setInteger4(const unsigned int programID, const char* name, int value[4]);
// sets 2x2 float matrix uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setMatrix2(const unsigned int programID, const char* name, mat2 value);
// sets 3x3 float matrix uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setMatrix3(const unsigned int programID, const char* name, mat3 value);
// sets 4x4 float matrix uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setMatrix4(const unsigned int programID, const char* name, mat4 value);

#endif