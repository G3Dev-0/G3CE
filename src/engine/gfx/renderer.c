/*
RENDERER:
Contains some useful rendering functions
*/

#include <glad/glad.h>

#include "engine/utils/console.h"

#include "engine/gfx/renderer.h"
#include "engine/gfx/shader.h"

float clearColor[4] = { 1, 1, 1, 1 };
Camera* activeCamera = NULL;
int activeShader = 0;

// sets the clear color with RGBA values (default color is white (1, 1, 1, 1))
void renderer_setGLClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
}

// sets GL polygon mode (either to GL_POINT, GL_LINE or GL_FILL (default one))
void renderer_setGLPolygonMode(unsigned int mode) {
    if (mode != GL_POINT && mode != GL_LINE && mode != GL_FILL) {
        console_warning("Invalid polygon mode for %u", mode);
        return;
    }
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

// sets GL cull mode (either to GL_FRONT, GL_BACK (default), GL_FRONT_AND_BACK or 0 (disable face culling))
void renderer_setGLCullMode(unsigned int mode) {
    if (mode != GL_FRONT && mode != GL_BACK && mode != GL_FRONT_AND_BACK && mode != 0) {
        console_warning("Invalid cull mode for %u", mode);
        return;
    }

    if (mode == 0) {
        glDisable(GL_CULL_FACE);
    } else {
        glEnable(GL_CULL_FACE);
        glCullFace(mode);
    }
}

// sets GL depth test function
// the fragments depth value goes from 0.0 (near) to 1.0 (far),
// meaning GL_LESS should be the go-to depth testing function
// when not changing the projection matrix provided by G3CE
// KEEP IN MIND THAT IF YOU CHANGE THE PROJECTION MATRIX
// YOU COULD HAVE REVERSED / CHANGED THE NEAR - FAR FRAGMENT DEPTH VALUE MAPPING
// depthFunction can either be:
// GL_ALWAYS    =    The depth test always passes (same as disabling the depth test, the objects get rendered in the order they are rendered in code)
// GL_NEVER  	=    The depth test never passes
// GL_LESS   	=    Passes if the fragment's depth value is less than the stored depth value
// GL_EQUAL  	=    Passes if the fragment's depth value is equal to the stored depth value
// GL_LEQUAL    =    Passes if the fragment's depth value is less than or equal to the stored depth value
// GL_GREATER   =    Passes if the fragment's depth value is greater than the stored depth value
// GL_NOTEQUAL  =    Passes if the fragment's depth value is not equal to the stored depth value
// GL_GEQUAL    =    Passes if the fragment's depth value is greater than or equal to the stored depth value
// 0            =    Disables OpenGL depth test
void renderer_setGLDepthTest(unsigned int depthFunction) {
    if (depthFunction != GL_ALWAYS
        && depthFunction != GL_NEVER
        && depthFunction != GL_LESS
        && depthFunction != GL_EQUAL
        && depthFunction != GL_LEQUAL
        && depthFunction != GL_GREATER
        && depthFunction != GL_NOTEQUAL
        && depthFunction != GL_GEQUAL
        && depthFunction != 0) {
        console_warning("Invalid depth function for %u", depthFunction);
        return;
    }

    if (depthFunction == 0) {
        glDisable(GL_DEPTH_TEST);
    } else {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(depthFunction);
        glDepthMask(GL_TRUE);
    }
}

/*
Uses a shader.
Parameters:
    - shader (unsigned int): the shader program id
*/
void renderer_useShader(unsigned int shader) {
    glUseProgram(shader);
    activeShader = shader;
}

/*
Binds a texture.
Parameters:
    - texture (unsigned int): the texture id
    - unit (unsigned int): the texture unit to bind the texture to
*/
void renderer_bindTexture(unsigned int texture, unsigned int unit) {
    if (unit > 32) {
        console_warning("Invalid texture unit for %u. There are a total number of 32 texture units", unit);
        return;
    }
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

/*
Uses a camera.
Parameters:
    - camera (Camera*): the pointer to the camera to use
*/
void renderer_useCamera(Camera* camera) {
    activeCamera = camera;
}

// prepares for rendering (automatically updates the view matrix is a camera and a shader with a view matrix uniform are being currently used)
void renderer_prepare() {
    if (shader_hasUniform(activeShader, "view")) {
        console_warning("The current shader has no view matrix uniform! Try using another shader");
    }
    if (activeCamera != NULL && activeShader != 0) {
        shader_setMatrix4(activeShader, "view", camera_getViewMatrix(activeCamera));
    }
}

/*
Renders a given mesh.
Parameters:
    - mesh (Mesh): the mesh pointer
*/
void renderer_renderMesh(Mesh* mesh) {
    // bind the mesh texture if needed
    if (mesh->texture > 0) {
        renderer_bindTexture(mesh->texture, mesh->textureUnit);
    }
    // bind the mesh VAO
    glBindVertexArray(mesh->vao);
    // draw
    glDrawElements(mesh->drawMode, mesh->indicesLength, GL_UNSIGNED_INT, 0);

    // unbind
    glBindVertexArray(0);
    
    if (mesh->texture > 0) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

// renders the given object using the shader assigned to the object via object_assignShader()
// (or the currently active one if the assigned shader is 0)
// automatically called renderer_prepare() before rendering the object,
// so you don't need to call it manually before calling this function
void renderer_renderObject(Object* object) {
    // bind the shader assigned to the given object
    if (object->shader > 0) {
        renderer_useShader(object->shader);
    }

    // assign the view matrix
    renderer_prepare();

    // assign the model matrix
    if (shader_hasUniform(activeShader, "model")) {
        shader_setMatrix4(activeShader, "model", transform_getModelMatrix(&(object->transform)));
    } else {
        console_warning("The current shader has no model matrix uniform! Try using another shader");
        return;
    }

    // render the mesh
    renderer_renderMesh(&(object->mesh));
}