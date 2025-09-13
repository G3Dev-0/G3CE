# G3CE
**G3**Dev's **C** **E**ngine is an OpenGL engine useful for running simulations, creating games and for general purpose rendering.

## Table of Contents
+ [**Using G3CE**](#using-g3ce)
+ [**Engine modules**](#engine-modules)

    **Core**
    - [**App**](#app)
    - [**Window**](#window)
    - [**Input**](#input)

    **Math**
    - [**Linear Algebra**](#linear-algebra)
    - [**Transform**](#transform)
    - [**Camera**](#camera)

    **Graphics**
    - [**Renderer**](#renderer)
    - [**Shader**](#shader)
    - [**Mesh**](#mesh)
    - [**Texture**](#texture)
    
    **Utils**
    - [**Console**](#console)
    - [**File**](#file)
+ [**Using the engine**](#using-the-engine)
+ [**Used technologies**](#used-technologies)
+ [**Version history**](#version-history)
+ [**About**](#about)

### Using G3CE [#](#table-of-contents)
To use the library you can either import it or test it's features by running a file containing the necessary code. Said code can be manually written every time or it can be simply copied and pasted into a file from the `template.c` file.

### Engine modules [#](#table-of-contents)
The engine structure is based on modules.\
Each one has its own functions useful for building your app.

#### App [#](#table-of-contents)
This module contains all the functions that handle app creation, loop and destruction.
To start the app you first create the app by calling `app_create(int width, int height, char* title, bool resizable)`, giving the window parameters.

To actually show the window and start the program you should call the `app_loop()`.\
This function will enter the main loop and actually run the app.\
Remember that `app_loop()` requires 4 `void (*f)()` type parameters.\
Those 4 parameters are the initialization, update, render and exit functions for your app. Each of them is called in a specific moment during runtime. Here are their purpuses:
- `void main_init()`: initialization function, it is called only once right before entering the main loop
- `void main_tick()`: update function, it is called once every frame before clearing the previous frame
- `void main_draw()`: rendering function, it is called once every frame right after clearing the previous frame
- `void main_exit()`: exit function, it is called only once after leaving the main loop, before terminating the app

Finally there are two functions:
+ `void app_requestClose()`: requests the app to close.\
It CANNOT be called outside of the app main loop
+ `void app_terminate()`: closes the app by terminating GLFW.\
This should NEVER be called and it is used internally by the engine. It's good practice to politely request GLFW to close the program instead on killing it on the fly.

#### Window [#](#table-of-contents)
This module contains all the GLFW window related functions. For the simplest app you can run, you might even never touch this module, as the main window parameters (`width`, `height` and `title`) are passed to it by the [`app_create()`](#app) function.

Here are all the contained functions and their purpuse.
+ `GLFWwindow* window_create(int width, int height, char* title, bool resizable)`: creates the window with the given parameters
+ `void window_destroy()`: destroyes the GLFW window

**WINDOW CUSTOMIZATION**:
+ `void window_setTitle(char* title)`: sets the window title
+ `void window_setSize(int width, int height)`: sets the window size
+ `void window_setIcon(char* filename)`: sets the window icon
+ `void window_setFullscreen(bool fullscreen):` sets window fullscreen/windowed mode
+ `void window_toggleFullscreen():` toggles window fullscreen/windowed mode

#### Input [#](#table-of-contents)
This module contains all the useful handlers for keyboard and mouse input. Namely:
+ `bool input_isKeyPressed(int key):` returns true ONLY the first tick the key is pressed, then it returns false
+ `bool input_isKeyDown(int key)`: returns true EVERY tick the key is pressed, returns false if the key is not pressed
+ `bool input_isKeyReleased(int key)`: returns true ONLY the first tick the key is released, then it returns false
+ `bool input_isButtonPressed(int button)`: returns true ONLY the first tick the button is pressed, then it returns false
+ `bool input_isButtonDown(int button)`: returns true EVERY tick the button is pressed, returns false if the button is not pressed
+ `bool input_isButtonReleased(int button)`: returns true ONLY the first tick the button is released, then it returns false
+ `double input_getMouseX()`: returns the mouse x position in the window (0 to window_width - 1 from LEFT to RIGHT)
+ `double input_getMouseY()`: returns the mouse y position in the window (0 to window_height - 1 from TOP to BOTTOM)
+ `int input_getMouseScroll()`: returns the mouse scroll (0 when not scrolling, NEGATIVE when scrolling DOWNWARDS, POSITIVE when scrolling UPWARDS)

#### Linear Algebra [#](#table-of-contents)
The linear algebra (`linal.h`) module contains all the heavy math implementations for 2D, 3D and 4D vectors and matrices, as well as quaternions.

The used coordinate system is y-up, meaning in the three axes cartesian system the `x` and `z` components are the **horizontal** ones, while `y` is the **vertical** component.

Here are the main functions explenations.

**Stack allocator constructors**\
Those can be used to generate a quick ready-to-use vector, matrix or quaternion.\
+ `vecN vecN_new(float x, float y, ...)`: creates an N dimensional float vector where N is either 2, 3 or 4
+ `matN matN_new(float entries[N])`: creates an NxN float matrix.\
*Note:* `entries` is in row-major convention, meaning you shall give the entries **row by row**.
+ `quat quat_new(float w, float x, float y, float z)`: creates a new quaternion with `w` being the **scalar part** and `x`, `y`, `z` the components of the **vector part**

**Vector functions and operations**
+ `vecN vecN_zero()`: creates an N dimensional float vector with all components set to zero and returns it
+ `vecN vecN_one()`: creates an N dimensional float vector with all components set to one and returns it
+ `vecN vecN_sum(vecN v0, vecN v1)`: sums the two given vectors and returns the result
+ `vecN vecN_difference(vecN v0, vecN v1)`: subtracts the two given vectors and returns the result (equivalent to scaling `v1` by `-1` and summing it to `v0`)
+ `vecN vecN_scale(vecN v, float s)`: scales the given vector v by the given float s and returns the result
+ `float vecN_dot(vecN v0, vecN v1)`: evaluates the dot product of the two given vectors and returns the result
+ `vec3 vec3_cross(vec3 v0, vec3 v1)`: evaluates the cross product of the two given 3D vectors and returns the result
+ `vecN vecN_negate(vecN v, unsigned char target)`: multiplies the target components of the given vector by `-1`.\
Target can either be `TARGET_X`, `TARGET_Y`, `TARGET_Z` or a combination of these obtained by doing a **bitwise OR** between the needed targets.
E.g.: `TARGET_X | TARGET_Y` will negate the **x** and **y** component, but it will leave the **z** component unchanged.
+ `float vecN_magnitude(vecN v)`: evaluates the magnitude of the given vector and returns the result
+ `vecN vecN_normalize(vecN v)`: normalizes the given vector and returns the result

**Matrix functions and operations**
+ `matN matN_zero()`: creates an NxN matrix with all entries set to zero and returns it
+ `matN matN_one()`: creates an NxN matrix with all entries set to one and returns it
+ `matN matN_identity()`: creates an NxN identity matrix (a matrix with all entries set to zero apart from the ones in the main diagonal which are all set to one) and returns it
+ `mat2 mat2_rotation(float angle)`: creates a 2x2 rotation matrix based on the given angle in degrees
+ `mat2 mat2_scaling(vec2 scaling)`: creates a 2x2 scaling matrix based on the given scaling vector
+ `mat3 mat3_rotation(unsigned char axes, float angle)`: creates a 3x3 rotation matrix based on the given angle in degrees and the axes around which the rotation has to be applied.\
Axes can either be `AXIS_X`, `AXIS_Y`, `AXIS_Z` or a combination of these obtained by doing **bitwise OR** between the needed axes.
E.g.: `AXIS_X | AXIS_Y` will apply the rotation both around the **x axis** and the **y axis**, but **not** around the **z axis**.
+ `mat3 mat3_scaling(vec3 scaling)`: creates a 3x3 scaling matrix based on the given scaling vector
+ `mat4 mat4_translation(vec3 translation)`: creates a 4x4 translation matrix based on the given translation vector
+ `mat4 mat4_rotation(vec3 axis, float angle)`: creates a 4x4 rotation matrix based on the given axis direction (`vec3 axis`) and the given angle in degrees
+ `mat4 mat4_eulerRotation(vec3 angles)`: creates a 4x4 rotation matrix based on the given Tait-Bryan angles (pitch, yaw, roll) in degrees.\
**Pitch** is the rotation around the **x axis**, **yaw** is around the **y axis** and **roll** is the rotation around the **z axis**.
+ `mat4 mat4_scaling(vec3 scaling)`: creates a 4x4 scaling matrix based on the given scaling vector

**Projection matrices**
+ `mat4 matrix_orthographic_projection(float left, float right, float bottom, float top, float near, float far)`: returns an orthographic projection matrix given the projection parameters
+ `mat4 matrix_perspective_projection(int width, int height, float fov, float near, float far)`: returns a perspective projection matrix given the projection parameters.\
Width and height are the size of the window, fov is the field of view angle in degrees, near and far are the distances of the camera from the near and far planes respectively.
+ `matN matN_sum(matN m0, matN m1)`: sums the two given matrices and returns the result
+ `matN matN_difference(matN m0, matN m1)`: subtracts the two given matrices and returns the result (equivalent to scaling one of the two matrices by `-1` and summing it to the other one)
+ `matN matN_scale(matN m, float s)`: scales the given matrix by the given float s and returns the result
+ `matN matN_multiply(matN m0, matN m1)`: multiplyes the two given matrices and returns the result
+ `matN matN_transpose(matN m)`: transposes the given matrix and returns the result
+ `matN matN_negate(matN m)`: scales the whole matrix by -1 and returns the result

**Quaternions functions and operations**
+ `quat quat_zero()`: creates a quaternion with all components set to zero and returns it
+ `quat quat_identity()`: creates an identity quaternion (a quaternion with the scalar part set to one and the vector part being a zero vector)
+ `quat_rotation(vec3 axis, float angle)`: creates a rotation quaternion based on the given axis direction (`vec3 axis`) and the given angle in degrees, and returns it
+ `quat quat_multiply(quat q0, quat q1)`: multiplies the two given quaternions and returns the result

**Mixed operations**
+ `vecN matN_vecN_multiply(matN m, vecN v)`: multiplies the given matrix by the given vector and returns the result
+ `mat4 quat_to_mat4(quat q)`: converts a rotation quaternion to a 4D rotation matrix and returns the result
+ `quat mat4_to_quat(mat4 m)`: converts a 4D rotation matrix to a rotation quaternion and returns the result

**Output functions**
+ `void print_vecN(vecN v, unsigned int precision)`: prints out the given vector with the specified float digit number (`unsigned int precision`)
+ `void print_matN(matN m, unsigned int precision)`: prints out the given matrix with the specified float digit number (`unsigned int precision`)
+ `void print_quat(quat q, unsigned int precision)`: prints out the given quaternion with the specified float digit number (`unsigned int precision`)

#### Translate [#](#table-of-contents)
This module represent the transform object. A transform is essentially a collection of three vectors representing the position, rotation and scale of an object.\
It can be assigned to a used along with a Mesh to create a basic object that has a model to render and a place in the virtual world where to live.

Transforms are dynamically allocated on the heap via `malloc()` and thus MUST be destroyed via `transform_destroy(Transform* t)` to prevent memory leaks!

You can access the transform `position`, `rotation` and `scale` via the arrow operator:
```C
Transform* transform = transform_create();

transform->position;
transform->rotation;
transform->scale;

transform_destroy(transform);
```

Here are the operations you can perform ona  transform:
+ `Transform* transform_create()`: creates a blank transform (position and rotations will be zero vectors while scale will be a one vector) allocated on the heap and returns the pointer to it
+ `void transform_destroy(Transform* t)`: destroyes a previously created transform

+ `void transform_changePosition(Transform* t, vec3 translation)`: increments the given transform position by the given translation vector (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
+ `void transform_changeRotation(Transform* t, vec3 rotation)`: increments the given transform rotation by the given rotation vector (pitch, yaw, roll) (angles are in degrees)
+ `void transform_changeScale(Transform* t, vec3 scaling)`: increment the the given transform scale by the given scaling vector (xs, ys, zs)

+ `mat4 transform_getModelMatrix(Transform* t)`: calculates the model matrix for the given transform and returns it

#### Camera [#](#table-of-contents)
Similarly to the transform module, the camera module represents the camera object.

You can access the camera `position`, `pitch` and `yaw` via the arrow operator:
```C
Camera* camera = camera_create();

camera->position;
camera->pitch;
camera->yaw;

camera_destroy(camera);
```

You can perform the following operations:
+ `Camera* camera_create()`: creates a camera positioned at the world origin (0, 0, 0) and looking forward with pitch and yaw angles both set to zero.\
REMEMBER you MUST DESTROY the camera via camera_destroy()!
+ `void camera_destroy(Camera* c)`: destroys the given camera

+ `void camera_move(Camera* c, vec3 move)`: moves the given camera by the given move vector
+ `void camera_rotate(Camera* c, float xr, float yr)`: rotates the camera by the given angles (`xr` and `yr` being the rotation angles around the **x** and **y axes** respectively. Also known as **pitch** and **yaw**)

+ `void camera_getViewMatrix(Camera* c)`: calculates the view matrix for the given camera and returns it

#### Renderer [#](#table-of-contents)
The renderer module can be used to render meshed, enable shaders and have rapid access to some OpenGL functions.

+ `void renderer_setGLClearColor(float r, float g, float b, float a)`: sets the clear color with RGBA values (default color is white (1, 1, 1, 1))
+ `void renderer_setGLPolygonMode(unsigned int mode)`: sets GL polygon mode (either to GL_POINT, GL_LINE or GL_FILL (default one))
+ `void renderer_setGLCullMode(unsigned int mode)`: sets GL cull mode (either to GL_FRONT, GL_BACK (default), GL_FRONT_AND_BACK or -1 (disable face culling))

+ `void renderer_useShader(unsigned int shader)`: uses a shader.\
**Parameters:**
    - shader (*unsigned int*): the shader program id
+ `void renderer_bindTexture(unsigned int texture, unsigned int unit)`: binds a texture.
**Parameters:**
    - texture (*unsigend int*): the shader program id
+ `void renderer_renderMesh(Mesh* mesh)`: renders a given mesh.\
**Parameters:**
    - mesh (*Mesh**): the mesh pointer

#### Shader [#](#table-of-contents)
Shaders are the GPU code that allows you to render anything on the screen. They are written in GLSL (GL Shading Language). With this module you can easily load them in code and use them when rendering.
+ `unsigned int shader_create(char* vertexPath, char* fragmentPath)`: creates a shader program from the given vertex and fragment shader codes ("./file" means it is in "g3ce") and returns its program ID
+ `void shader_destroy(unsigned int programID)`: destroys the given shader
+ `void setBoolean(const unsigned int programID, const char* name, bool value)`: sets boolean uniform
+ `void setFloat(const unsigned int programID, const char* name, float value)`: sets float uniform
+ `void setInteger(const unsigned int programID, const char* name, int value)`: sets integer uniform
+ `void setFloat2(const unsigned int programID, const char* name, float value[2])`: sets float vector 2 uniform
+ `void setInteger2(const unsigned int programID, const char* name, int value[2])`: sets int vector 2 uniform
+ `void setFloat3(const unsigned int programID, const char* name, float value[3])`: sets float vector 3 uniform
+ `void setInteger3(const unsigned int programID, const char* name, int value[3])`: sets int vector 3 uniform
+ `void setFloat4(const unsigned int programID, const char* name, float value[4])`: sets float vector 4 uniform
+ `void setInteger4(const unsigned int programID, const char* name, int value[4])`: sets int vector 4 uniform

**Remember: a shader must always be destroyed when not used anymore!**

#### Mesh [#](#table-of-contents)
With the mesh module, you can easily create simple meshes starting from vertices, indices and a draw mode.
After creating a mesh you can easily draw the mesh using a certain shader.
+ `Mesh* mesh_create(float* vertices, int verticesSize, unsigned int* indices, int indicesSize, int vertexLength, int drawMode)`: creates a new mesh object and returns a pointer to it.
You MUST call mesh_destroy(Mesh*) once the mesh is not used anymore
in order to free the allocated memory
All the vertex data must be put into the same vertices array.\
**Parameters:**
    - vertices (float*): pointer to float array containing ALL the vertex data (positions, colors, UVs, normals, etc...)
    - verticesSize (unsigned int): sizeof(vertices)
    - indices (unsigned int*): pointer to integer array containing the indices that specify the order in which the vertices must be rendered
    - indicesSize (unsigned int): sizeof(indices)
    - vertexLength (unsigned int): the number of floats that defines a vertex (e.g.: 3 for 3D position + 4 for RGBA color = 7)
    - drawMode (unsigned int): the drawing mode OpenGL has to use (GL_TRIANGLES, GL_QUADS, etc...)

    **Returns:**\
    The pointer to the mesh struct that has been created. It points to dynamically allocated memory, so you MUST call mesh_destroy(Mesh*) that handles the free() procedure
+ `void mesh_destroy(Mesh* mesh)`: destroys the given mesh object.\
**Parameters:**
    - mesh (Mesh*): the mesh to destroy
+ `void mesh_registerVertexAttribute(Mesh* mesh, int attributeLocation, int size)`: registers a vertex attribute of type float for the given mesh.
**Parameters:**
    - mesh (*Mesh**): the pointer to the mesh to associate the new vertex float attribute
    - attributeLocation (*unsigned int*): the attribute location in the shader
    - size (*unsigned int*): number of floats that composes a vertex attribute (e.g.: 2 for UV coordinates, 3 for 3D positions, 4 for RGBA colors)
+ `void mesh_assignTexture(Mesh* mesh, unsigned int texture, unsigned int unit)`: assings a texture to a given mesh via a texture id (this means that the texture will be automatically bound when rendering the mesh via renderer_renderMesh()).
**Parameters:**
    - texture (*unsigned int*): the texture id
    - unit (*unsigned int*): the texture unit to attach the texture to

#### Texture [#](#table-of-contents)
The texture module can be used to rapidly deal with 2D textures.
+ `unsigned int texture_create(char* path, bool hasTransparency)`: creates a texture loading an image from the given path ("./file" means it is in "g3ce").\
REMEMBER TO DESTROY IT BY CALLING texture_destroy()!\
If you assign the texture to a mesh via mesh_assignTexture() destroying the mesh will also destroy the texture.
+ `void texture_destroy(unsigned int texture)`: destroys a given texture
+ `void texture_setFilter(unsigned int texture, unsigned int filter, unsigned int mode)`: sets the filter for a given texture.
**Parameters:**
    - texture (*unsigned int*): the texture id
    - filter (*unsigned int*): the filter to set the mode for (either GL_TEXTURE_MIN_FILTER for minifying textures or GL_TEXTURE_MAG_FILTER for magnifying textures)
    - mode (*unsigned int*): the filter mode to set (either GL_NEAREST for crispy/pixelated textures (it samples the nearest pixel color) or GL_LINEAR for a smoother texture (it interpolates the closer pixel colors))
+ `void texture_setWrapping(unsigned int texture, unsigned int wrap, unsigned int mode)`: sets the wrapping mode for a given texture.
**Parameters:**
    - texture (*unsigned int*): the texture id
    - wrap (*unsigned int*): the wrap to set the mode for (either GL_TEXTURE_WRAP_S for horizontal wrapping or GL_TEXTURE_WRAP_T for vertical wrapping)
    - mode (*unsigned int*): the wrap mode to set. It can be one of the following:
        + **GL_REPEAT** (the default one) repeats the texture indefinitively
        + **GL_MIRRORED_REPEAT** repeats the texture indefinitively but also mirrors it with each repeat
        + **GL_CLAMP_TO_EDGE** clamps UVs between 0 and 1
        + **GL_CLAMP_TO_BORDER** UVs outside of the range [0, 1] are given a user-specified color
+ `void texture_setBorderColor(unsigned int texture, float r, float g, float b, float a)`: sets the border color for when OpenGL wrapping is set to **GL_CLAMP_TO_BORDER** mode

**Remember: a mesh must always be destroyed when not used anymore!**

#### Console [#](#table-of-contents)
This module has some cooler output functions that allow you to better organize your outputs.
+ `void console_output(const char* format, ...)`: generic output (just like a printf())
+ `void console_info(const char* format, ...)`: info log level (uses the "[INFO]: " prefix)
+ `void console_log(const char* format, ...)`: log log level (uses the "[LOG]: " prefix and outputs in green color)
+ `void console_warning(const char* format, ...)`: warning log level (uses the "[WARNING]: " prefix and outputs in orange color)
+ `void console_error(const char* format, ...)`: error log level (uses the "[ERROR]: " prefix and outputs in red color)
+ `void console_debug(const char* format, ...)`: debug log level (uses the "[DEBUG]: " prefix and outputs in blue color)

#### File [#](#table-of-contents)
The file module has some file handling utility functions, namely:
+ `bool file_write(char* path, char* content)`: writes content to a file at path ("./file" means it is in "g3ce")
+ `char* file_read(char* path)`: returns the content of a file at path ("./file" means it is in "g3ce"), YOU MUST FREE THE RETURN VALUE by calling stdlib.free()!
+ `int file_remove(char* path)`: removes a file at path ("./file" means it is in "g3ce")

### Using the engine [#](#table-of-contents)
In order to use the engine you have to create a `main.c` file where you can run all your logic and rendering code.\
After doing so, you'll be able to start the program by running `cmd/run.sh`. This will build the project and run it using `int main()` function in `main.c` as the program entry point.\
You can set up a simple program as follows:
```C
/*
This simple program renders a colorful quad at the center of the screen.
*/
#include "engine/app.h"
#include "engine/core/window.h"
#include "engine/core/input.h"
#include "engine/gfx/mesh.h"
#include "engine/gfx/renderer.h"
#include "engine/gfx/shader.h"

// you can also declare those four functions in a "main.h" file for good practice
void main_init();
void main_tick();
void main_draw();
void main_exit();

int main() {
    // create the app
    app_create(800, 600, "My GLFW Window", 1);
    // main app loop
    app_loop(main_init, main_tick, main_draw, main_exit);
    // close the app when the loop is broken (you can break out of the loop ONLY by calling app_requestClose())
    app_terminate();
    
    return 0;
}

unsigned int vao;
unsigned int color_shader;
Mesh* mesh;

// init function (called before entering the app main loop)
void main_init() {
    color_shader = shader_create("./assets/shaders/color_vertex.glsl", "./assets/shaders/color_fragment.glsl");

    float vertices[] = {
        // position         // color
        -0.5, -0.5, 0.0,    1.0, 0.0, 0.0, 0.0,
        0.5, -0.5, 0.0,     0.0, 1.0, 0.0, 0.0,
        0.5, 0.5, 0.0,      0.0, 0.0, 1.0, 0.0,
        -0.5, 0.5, 0.0,     1.0, 1.0, 1.0, 0.0
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    // create a mesh
    mesh = mesh_create(vertices, sizeof(vertices), indices, sizeof(indices), 3+4, GL_TRIANGLES);
    mesh_registerVertexAttribute(mesh, 0, 3); // position attribute
    mesh_registerVertexAttribute(mesh, 1, 4); // color attribute
}

// tick function (called once every frame, here you should put all you update code)
void main_tick() {
    // close the app when the ESCAPE key is pressed
    if (input_isKeyPressed(GLFW_KEY_ESCAPE)) {
        app_requestClose();
    }

    // toggle fullscreen mode when the F11 key is pressed
    if (input_isKeyPressed(GLFW_KEY_F11)) {
        window_toggleFullscreen();
    }
}

// draw function (called once every frame, here you should put all you rendering code)
void main_draw() {
    renderer_useShader(color_shader);
    renderer_renderMesh(mesh);
}

// exit function (called after breaking out from the app main loop, before terminating the app)
void main_exit() {
    mesh_destroy(mesh);
    shader_destroy(color_shader);
}
```

Here is also the shader code:\
**Vertex shader:**
```GLSL
#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iCol;

out vec4 oCol;

void main() {
    oCol = iCol;
    gl_Position = vec4(iPos.xyz, 1.0);
}
```

**Fragment shader:**
```GLSL
#version 330 core

in vec4 oCol;

out vec4 fragColor;

void main() {
    fragColor = oCol;
}
```

### Used technologies [#](#table-of-contents)
- **C**\
Programming language\
Version: *Standard C23*\
Home page: https://www.c-language.org/

- **OpenGL**\
Graphics library\
Home page: https://www.opengl.org/

- **GLUtils**\
OpenGL Utility Toolkit\
Home page: https://www.opengl.org/resources/libraries/glut/glut_downloads.php

- **GLAD**\
OpenGL loader generator\
Home page: https://glew.sourceforge.net/

- **GLFW**\
Window context and input handler\
Home page: https://www.glfw.org/

- **STB Image**\
Image loader\
Home page: https://github.com/nothings/stb

### Version history [#](#table-of-contents)
+ **v1.0 b13092025-1:** added transform and camera objects
+ **v1.0 b13092025-0:** added linear algebra module
+ **v1.0 b12092025-0:** added 2D texture support
+ **v1.0 b11092025-0:** improved mesh implementation, added a renderer module to easily deals with some OpenGL functions
+ **v1.0 b08092025-0:** implemented shader uniform handling, fixed offset in vertex attribute location registration
+ **v1.0 b06092025-0:** implemented shader and mesh utilities
+ **v1.0 b01092025-0:** implemented functions for app handling, window and input

### About [#](#table-of-contents)
Made by G3Dev\
v1.0 b13092025-1