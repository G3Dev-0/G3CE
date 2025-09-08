/*
RENDERER:
Contains some useful rendering functions
*/

#include "engine/gfx/renderer.h"

float clearColor[4] = { 1, 1, 1, 1 };

// sets the clear color with RGBA values (default color is white (1, 1, 1, 1))
void renderer_setGLClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
}