/*
SHADER:
Shader handler
*/

#include <stdlib.h>

#include <glad/glad.h>

#include "engine/utils/file.h"
#include "engine/utils/console.h"

#include "engine/gfx/shader.h"

// creates a shader from a file path ("./file" means it is in "g3ce")
unsigned int shader_get(char* path, int type) {
    const char* source = file_read(path);
    if (source == NULL) return -1;

    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    
    free((void*) source); // FREE THE RETURN VALUE OF file_read(path);
    
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

// creates a shader program from the given vertex and fragment shader codes ("./file" means it is in "g3ce")
unsigned int shader_create(char* vertexPath, char* fragmentPath) {
    unsigned int vertexID = shader_get(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentID = shader_get(fragmentPath, GL_FRAGMENT_SHADER);

    if (vertexID == -1 || fragmentID == -1) {
        console_error("Could not create shader program with shaders at \"%s\" (vertex) \"%s\" (fragment)", vertexPath, fragmentPath);
        return -1;
    }

    // create program
    unsigned int programID = glCreateProgram();
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

// destroys the given shader
void shader_destroy(unsigned int programID) {
    glDeleteProgram(programID);
}

// UNIFORMs
// returns true if the given shader has a uniform with the given name, false othewrise
bool shader_hasUniform(const unsigned int programID, const char* name) {
    int location = glGetUniformLocation(programID, name);
    return location != -1;
}
// sets boolean uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setBoolean(const unsigned int programID, const char* name, bool value) {
    int location = glGetUniformLocation(programID, name);
    glUniform1i(location, value);
}
// sets float uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setFloat(const unsigned int programID, const char* name, float value) {
    int location = glGetUniformLocation(programID, name);
    glUniform1f(location, value);
}
// sets integer uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setInteger(const unsigned int programID, const char* name, int value) {
    int location = glGetUniformLocation(programID, name);
    glUniform1i(location, value);
}
// sets float vector 2 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setFloat2(const unsigned int programID, const char* name, vec2 value) {
    int location = glGetUniformLocation(programID, name);
    glUniform2f(location, value.x, value.y);
}
// sets int vector 2 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setInteger2(const unsigned int programID, const char* name, int value[2]) {
    int location = glGetUniformLocation(programID, name);
    glUniform2i(location, value[0], value[1]);
}
// sets float vector 3 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setFloat3(const unsigned int programID, const char* name, vec3 value) {
    int location = glGetUniformLocation(programID, name);
    glUniform3f(location, value.x, value.y, value.z);
}
// sets int vector 3 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setInteger3(const unsigned int programID, const char* name, int value[3]) {
    int location = glGetUniformLocation(programID, name);
    glUniform3i(location, value[0], value[1], value[2]);
}
// sets float vector 4 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setFloat4(const unsigned int programID, const char* name, vec4 value) {
    int location = glGetUniformLocation(programID, name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}
// sets int vector 4 uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setInteger4(const unsigned int programID, const char* name, int value[4]) {
    int location = glGetUniformLocation(programID, name);
    glUniform4i(location, value[0], value[1], value[2], value[3]);
}
// sets 2x2 float matrix uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setMatrix2(const unsigned int programID, const char* name, mat2 value) {
    int location = glGetUniformLocation(programID, name);
    // GL_TRUE is there to transpose the matrix as glUniformMatrix2fv() uses column-major order while linal.h uses row-major order
    glUniformMatrix2fv(location, 1, GL_TRUE, value.entries);
}
// sets 3x3 float matrix uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setMatrix3(const unsigned int programID, const char* name, mat3 value) {
    int location = glGetUniformLocation(programID, name);
    // GL_TRUE is there to transpose the matrix as glUniformMatrix2fv() uses column-major order while linal.h uses row-major order
    glUniformMatrix3fv(location, 1, GL_TRUE, value.entries);
}
// sets 4x4 float matrix uniform
// YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER,
// so remember to call renderer_useShader(int shader) first!
void shader_setMatrix4(const unsigned int programID, const char* name, mat4 value) {
    int location = glGetUniformLocation(programID, name);
    // GL_TRUE is there to transpose the matrix as glUniformMatrix2fv() uses column-major order while linal.h uses row-major order
    glUniformMatrix4fv(location, 1, GL_TRUE, value.entries);
}