/*
RENDERER:
Contains some useful rendering functions
*/

#ifndef RENDERER_H
#define RENDERER_H

#include "engine/gfx/mesh.h"

extern float clearColor[4];

// TODO: put all rendering preparation and drawing functions here to have a more centralized system (draw mesh, use shader, and so on...)

// sets the clear color with RGBA values (default color is white (1, 1, 1, 1))
void renderer_setGLClearColor(float r, float g, float b, float a);
// sets GL polygon mode (either to GL_POINT, GL_LINE or GL_FILL (default one))
void renderer_setGLPolygonMode(int mode);
// sets GL cull mode (either to GL_FRONT, GL_BACK (default), GL_FRONT_AND_BACK or -1 (disable face culling))
void renderer_setGLCullMode(int mode);

/*
Uses a shader.
Arguments:
    - shader (int): the shader program id
*/
void renderer_useShader(int shader);

/*
Renders a given mesh.
Arguments:
    - mesh (Mesh): the mesh pointer
*/
void renderer_renderMesh(Mesh* mesh);

#endif