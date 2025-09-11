/*
RENDERER:
Contains some useful rendering functions
*/

#include <glad/glad.h>

#include "engine/utils/console.h"

#include "engine/gfx/renderer.h"

float clearColor[4] = { 1, 1, 1, 1 };

// sets the clear color with RGBA values (default color is white (1, 1, 1, 1))
void renderer_setGLClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
}

// sets GL polygon mode (either to GL_POINT, GL_LINE or GL_FILL (default one))
void renderer_setGLPolygonMode(int mode) {
    if (mode != GL_POINT && mode != GL_LINE && mode != GL_FILL) {
        console_warning("Invalid polygon mode for %d", mode);
        return;
    }
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

// sets GL cull mode (either to GL_FRONT, GL_BACK (default), GL_FRONT_AND_BACK or -1 (disable face culling))
void renderer_setGLCullMode(int mode) {
    if (mode != GL_FRONT && mode != GL_BACK && mode != GL_FRONT_AND_BACK && mode != -1) {
        console_warning("Invalid cull mode for %d", mode);
        return;
    }

    if (mode == -1) glDisable(GL_CULL_FACE);
    else glEnable(GL_CULL_FACE);
    glCullFace(mode);
}

/*
Uses a shader.
Arguments:
    - shader (int): the shader program id
*/
void renderer_useShader(int shader) {
    glUseProgram(shader);
}

/*
Renders a given mesh.
Arguments:
    - mesh (Mesh): the mesh pointer
*/
void renderer_renderMesh(Mesh* mesh) {
    glBindVertexArray(mesh->vao);
    glDrawElements(mesh->drawMode, mesh->indicesLength, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}