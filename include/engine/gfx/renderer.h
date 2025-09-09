/*
RENDERER:
Contains some useful rendering functions
*/

#ifndef RENDERER_H
#define RENDERER_H

extern float clearColor[4];

// sets the clear color with RGBA values (default color is white (1, 1, 1, 1))
void renderer_setGLClearColor(float r, float g, float b, float a);

#endif