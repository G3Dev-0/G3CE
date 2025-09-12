/*
TEXTURE:
2D Texture handler module
*/

#include <glad/glad.h>
#include <stbi/stb_image.h>

#include "engine/utils/console.h"

#include "engine/gfx/texture.h"

// creates a texture loading an image from the given path ("./file" means it is in "g3ce").
// REMEMBER TO DESTROY IT BY CALLING texture_destroy()!
// If you assign the texture to a mesh via mesh_assignTexture() destroying the mesh will also destroy the texture.
unsigned int texture_create(char* path, bool hasTransparency) {
    // generate the texture
    unsigned int texture;
    glGenTextures(1, &texture);
    // bind the texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // load image file content into the bound texture
    int width, height, channels;
    unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, hasTransparency ? GL_RGBA : GL_RGB, width, height, 0, hasTransparency ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        // either do this or set filtering and wrapping parameters before rendering
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        console_error("Failed to load texture at \"%s\"", path);
        return -1;
    }
    
    // free the stb image
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

// destroys a given texture
void texture_destroy(unsigned int texture) {
    glDeleteTextures(1, &texture);
}

/*
Sets the filter for a given texture.
Parameters:
    - texture (unsigned int): the texture id
    - filter (unsigned int): the filter to set the mode for (either GL_TEXTURE_MIN_FILTER for minifying textures or GL_TEXTURE_MAG_FILTER for magnifying textures)
    - mode (unsigned int): the filter mode to set (either GL_NEAREST for crispy/pixelated textures (it samples the nearest pixel color) or GL_LINEAR for a smoother texture (it interpolates the closer pixel colors))
*/
void texture_setFilter(unsigned int texture, unsigned int filter, unsigned int mode) {
    if (filter != GL_TEXTURE_MIN_FILTER && filter != GL_TEXTURE_MAG_FILTER) {
        console_warning("Invalid texture filter for %u", filter);
        return;
    }
    if (mode != GL_NEAREST && mode != GL_LINEAR) {
        console_warning("Invalid filter mode for %u", mode);
        return;
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTextureParameteri(GL_TEXTURE_2D, filter, mode);
    glBindTexture(GL_TEXTURE_2D, 0);
}

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
void texture_setWrapping(unsigned int texture, unsigned int wrap, unsigned int mode) {
    if (wrap != GL_TEXTURE_WRAP_S && wrap != GL_TEXTURE_WRAP_T) {
        console_warning("Invalid texture wrap for %u", wrap);
        return;
    }
    if (mode != GL_REPEAT && mode != GL_MIRRORED_REPEAT && mode != GL_CLAMP_TO_EDGE && mode != GL_CLAMP_TO_BORDER) {
        console_warning("Invalid wrap mode for %u", mode);
        return;
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTextureParameteri(GL_TEXTURE_2D, wrap, mode);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// sets the border color for when OpenGL wrapping is set to GL_CLAMP_TO_BORDER mode
void texture_setBorderColor(unsigned int texture, float r, float g, float b, float a) {
    glBindTexture(GL_TEXTURE_2D, texture);
    
    float color[] = { r, g, b, a };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}