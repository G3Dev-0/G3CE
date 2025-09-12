/*
TEXTURE:
2D Texture handler module
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdbool.h>

// creates a texture loading an image from the given path ("./file" means it is in "g3ce").
// REMEMBER TO DESTROY IT BY CALLING texture_destroy()!
// If you assign the texture to a mesh via mesh_assignTexture() destroying the mesh will also destroy the texture.
unsigned int texture_create(char* path, bool hasTransparency);
// destroys a given texture
void texture_destroy(unsigned int texture);

/*
Sets the filter for a given texture.
Parameters:
    - texture (unsigned int): the texture id
    - filter (unsigned int): the filter to set the mode for (either GL_TEXTURE_MIN_FILTER for minifying textures or GL_TEXTURE_MAG_FILTER for magnifying textures)
    - mode (unsigned int): the filter mode to set (either GL_NEAREST for crispy/pixelated textures (it samples the nearest pixel color) or GL_LINEAR for a smoother texture (it interpolates the closer pixel colors))
*/
void texture_setFilter(unsigned int texture, unsigned int filter, unsigned int mode);
/*
Sets the wrapping mode for a given texture.
Parameters:
    - texture (unsigned int): the texture id
    - wrap (unsigned int): the wrap to set the mode for (either GL_TEXTURE_WRAP_S for horizontal wrapping or GL_TEXTURE_WRAP_T for vertical wrapping)
    - mode (unsigned int): the wrap mode to set. It can be one of the following:
        + GL_REPEAT (the default one) repeats the texture indefinitively
        + GL_MIRRORED_REPEAT repeats the texture indefinitively but also mirrors it with each repeat
        + GL_CLAMP_TO_EDGE clamps UVs between 0 and 1
        + GL_CLAMP_TO_BORDER UVs outside of the range [0, 1] are given a user-specified color
*/
void texture_setWrapping(unsigned int texture, unsigned int wrap, unsigned int mode);
// sets the border color for when OpenGL wrapping is set to GL_CLAMP_TO_BORDER mode
void texture_setBorderColor(unsigned int texture, float r, float g, float b, float a);

#endif