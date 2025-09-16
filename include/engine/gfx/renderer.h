/*
RENDERER:
Contains some useful rendering functions
*/

#ifndef RENDERER_H
#define RENDERER_H

#include "engine/core/object.h"
#include "engine/math/camera.h"
#include "engine/gfx/mesh.h"

extern float clearColor[4];
extern Camera* activeCamera;
extern int activeShader;

// sets the clear color with RGBA values (default color is white (1, 1, 1, 1))
void renderer_setGLClearColor(float r, float g, float b, float a);
// sets GL polygon mode (either to GL_POINT, GL_LINE or GL_FILL (default one))
void renderer_setGLPolygonMode(unsigned int mode);
// sets GL cull mode (either to GL_FRONT, GL_BACK (default), GL_FRONT_AND_BACK or -1 (disable face culling))
void renderer_setGLCullMode(unsigned int mode);
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
void renderer_setGLDepthTest(unsigned int depthFunction);

/*
Uses a shader.
Parameters:
    - shader (unsigned int): the shader program id
*/
void renderer_useShader(unsigned int shader);

/*
Binds a texture.
Parameters:
    - texuture (unsigned int): the texture id
    - unit (unsigned int): the texture unit to bind the texture to
*/
void renderer_bindTexture(unsigned int texture, unsigned int unit);

/*
Uses a camera.
Parameters:
    - camera (Camera*): the pointer to the camera to use
*/
void renderer_useCamera(Camera* camera);

// prepares for rendering (automatically updates the view matrix is a camera and a shader with a view matrix uniform are being currently used)
void renderer_prepare();

/*
Renders a given mesh.
Parameters:
    - mesh (Mesh): the mesh pointer
*/
void renderer_renderMesh(Mesh* mesh);

// renders the given object using the shader assigned to the object via object_assignShader()
// (or the currently active one if the assigned shader is 0)
void renderer_renderObject(Object* object);

#endif