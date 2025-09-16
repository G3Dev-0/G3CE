# G3CE
**G3**Dev's **C** **E**ngine is an OpenGL engine useful for running simulations, creating games and for general purpose rendering.

## Table of Contents
+ [**Using G3CE**](#using-g3ce-)
+ [**Engine modules**](#engine-modules-)

    **Core**
    - [**App**](#app-)
    - [**Window**](#window-)
    - [**Input**](#input-)
    - [**Object**](#object-)

    **Math**
    - [**Linear Algebra**](#linear-algebra-)
    - [**Transform**](#transform-)
    - [**Camera**](#camera-)

    **Graphics**
    - [**Renderer**](#renderer-)
    - [**Shader**](#shader-)
    - [**Mesh**](#mesh-)
    - [**Texture**](#texture-)
    
    **Utils**
    - [**Console**](#console-)
    - [**File**](#file-)
+ [**Using the engine**](#using-the-engine-)
+ [**Some theory and explainations**](#some-theory-and-explainations-)
+ [**Used technologies**](#used-technologies-)
+ [**Version history**](#version-history-)
+ [**About**](#about-)

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
Remember that `app_loop()` requires 5 `void (*f)()` type parameters.\
Those 4 parameters are the initialization, update, render and exit functions for your app. Each of them is called in a specific moment during runtime. Here are their purpuses:
- `void main_init()`: initialization function, it is called only once right before entering the main loop
- `void main_tick()`: update function, it is called once every frame before clearing the previous frame
- `void main_draw()`: rendering function, it is called once every frame right after clearing the previous frame
- `void main_exit()`: exit function, it is called only once after leaving the main loop, before terminating the app
- `void on_resize()`: // // resize function (called once at the start after the main_init() call and once every time a window resize event occurs)

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

**WINDOW PARAMETERS**
+ `float window_getWidth()`: returns the window width
+ `float window_getHeight()`: returns the window height

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

#### Object [#](#table-of-contents)
Objects are a simplification for creating a virtual object in the virtual world.\
An object holds a `Mesh` and a `Transform`, as well as an assigned `shader`.
You can easily change the object position, rotation and scale.
In order to render an object you can call the `renderer_renderObject(Object* o)` function, which will perform the following operations in the following order:
1. bind the object shader if the assigned shader is not 0, otherwise it will keep using the currently bound shader
2. call `renderer_prepare()` to upload the currently active camera view matrix to the active shader
3. upload the given object transform model matrix to correctly position the given object in the world and render it in place
4. call `renderer_renderMesh()` to render the object mesh. This will also bind the texture assigned to the object mesh via mesh_assignTexture();

Here is the actual object implementation:
+ `Object object_new(Mesh mesh)`: creates a stack allocated object using the given mesh, with a blank transform an assigned shader = 0. It does not need to be destroyed

+ `Object* object_create(Mesh mesh)`: creates an object with a given mesh and a blank transform (by default the assigned shader is 0).\
YOU MUST DESTROY IT ONCE YOU'RE DONE WITH IT TO AVOID MEMORY LEAKS
+ `void object_destroy(Object* o)`: destroys the given object

+ `void object_setTransformByTransform(Object* o, Transform t)`: sets the given object transform to the given transform
+ `void object_setTransformByVectors(Object* o, vec3 position, vec3 rotation, vec3 scale)`: sets the given object transform vectors to the given transform vectors
+ `void object_setTransformByValues(Object* o, float x, float y, float z, float pitch, float yaw, float roll, float xs, float ys, float zs)`: sets the given object transform values to the given transform values

+ `void object_setPositionByVector(Object* o, vec3 position)`: sets the given object position to the given position vector
+ `void object_setRotationByVector(Object* o, vec3 rotation)`: sets the given object rotation to the given rotation vector
+ `void object_setScaleByVector(Object* o, vec3 scale)`: sets the given object scale to the given scale vector

+ `void object_setPositionByValues(Object* o, float x, float y, float z)`: sets the given object position to the given position values
+ `void object_setRotationByValues(Object* o, float pitch, float yaw, float roll)`: sets the given object rotation to the given rotation values
+ `void object_setScaleByValues(Object* o, float xs, float ys, float zs)`: sets the given object scale to the given scale values

+ `void object_changePositionByVector(Object* o, vec3 translation)`: increments the given object position by the given translation vector
+ `void object_changeRotationByVector(Object* o, vec3 rotation)`: increments the given object rotation by the given rotation vector
+ `void object_changeScaleByVector(Object* o, vec3 scaling)`: increments the given object scale by the given scaling vector

+ `void object_changePositionByValues(Object* o, float xm, float ym, float zm)`: increments the given object position by the given position values
+ `void object_changeRotationByValues(Object* o, float xr, float yr, float zr)`: increments the given object rotation by the given rotation values
+ `void object_changeScaleByValues(Object* o, float xs, float ys, float zs)`: increments the given object scale by the given scale values

+ `void object_assignShader(Object* o, unsigned int shader)`: assigns the given shader to the given object when calling renderer_renderObject(Object* o) the assigned shader will be bound if the assigned shader is 0, the renderer will keep using the currently bound shader

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
+ `mat4 matrix_getOrthographicProjection(float left, float right, float bottom, float top, float near, float far)`: returns an orthographic projection matrix given the projection parameters
+ `mat4 matrix_getPerspectiveProjection(float width, float height, float fov, float near, float far)`: returns a perspective projection matrix given the projection parameters.\
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

#### Transform [#](#table-of-contents)
This module represent the transform object. A transform is essentially a collection of three vectors representing the position, rotation and scale of an object.\
It can be assigned to a used along with a Mesh to create a basic object that has a model to render and a place in the virtual world where to live.

Transforms are dynamically allocated on the heap via `malloc()` and thus MUST be destroyed via `transform_destroy(Transform* t)` to prevent memory leaks!

You can access the transform `position`, `rotation` and `scale` via the arrow operator:
```C
Transform* transform = transform_create();

transform->position; // this is a vec3 from linal.h
transform->rotation; // this is a vec3 from linal.h
transform->scale; // this is a vec3 from linal.h

transform_destroy(transform);
```

Here are the operations you can perform ona  transform:
+ `Transform transform_new()`: creates a stack allocated blank transform and returns it. This does not need to be destroyed
+ `Transform* transform_create()`: creates a blank transform (position and rotations will be zero vectors while scale will be a one vector) allocated on the heap and returns the pointer to it
+ `void transform_destroy(Transform* t)`: destroyes a previously created transform

+ `void transform_setPosition(Transform* t, float x, float y, float z)`: sets the given transform position to the given position values (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
+ `void transform_setRotation(Transform* t, float pitch, float yaw, float roll)`: sets the given transform rotation to the given rotation values
+ `void transform_setScale(Transform* t, float xs, float ys, float zs)`: sets the given transform scale to the given scale values

+ `void transform_changePosition(Transform* t, vec3 translation)`: increments the given transform position by the given translation vector (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
+ `void transform_changeRotation(Transform* t, vec3 rotation)`: increments the given transform rotation by the given rotation vector (pitch, yaw, roll) (angles are in degrees)
+ `void transform_changeScale(Transform* t, vec3 scaling)`: increment the the given transform scale by the given scaling vector (xs, ys, zs)

+ `void transform_changePositionValues(Transform* t, float xm, float ym, float zm)`: increments the given transform position by the given translation values (x, y, z) (using right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
+ `void transform_changeRotationValues(Transform* t, float xr, float yr, float zr)`: increments the given transform rotation by the given rotation values (pitch, yaw, roll) (angles are in degrees)
+ `void transform_changeScaleValues(Transform* t, float xs, float ys, float zs)`: increment the the given transform scale by the given scaling values (xs, ys, zs)

+ `mat4 transform_getModelMatrix(Transform* t)`: calculates the model matrix for the given transform and returns it

#### Camera [#](#table-of-contents)
Similarly to the transform module, the camera module represents the camera object.

You can access the camera `position`, `pitch` and `yaw` via the arrow operator:
```C
Camera* camera = camera_create();

camera->position; // this is a vec3 from linal.h
camera->rotation; // this is a vec3 from linal.h

camera_destroy(camera);
```

You can perform the following operations:
+ `Camera* camera_create()`: creates a camera positioned at the world origin (0, 0, 0) and looking forward with rotation angles all set to zero.\
REMEMBER you MUST DESTROY the camera via camera_destroy()!
+ `void camera_destroy(Camera* c)`: destroys the given camera

**SETTERS**
+ `void camera_setPosition(Camera* c, float x, float y, float z)`: sets the given camera position to the given coordinates values
+ `void camera_setRotation(Camera* c, float pitch, float yaw, float roll)`: sets the given camera position to the given pitch, yaw and roll values

**OPERATIONS**
+ `void camera_moveByVector(Camera* c, vec3 move)`: moves the given camera by the given move vector
+ `void camera_move(Camera* c, float xm, float ym, float zm)`: moves the given camera by the given motion values
+ `void camera_rotateByVector(Camera* c, vec3 rotation)`: rotates the camera by the given rotation vector
+ `void camera_rotate(Camera* c, float xr, float yr, float zr)`: rotates the camera by the given angles

**CAMERA COORDINATE SYSTEM**
+ `vec3 camera_getPositiveX(Camera* c)`: returns the x axis direction of the camera centered coordinate system
+ `vec3 camera_getPositiveY(Camera* c)`: returns the y axis direction of the camera centered coordinate system
+ `vec3 camera_getPositiveZ(Camera* c)`: returns the z axis direction of the camera centered coordinate system

+ `vec3 camera_getForward(Camera* c)`: returns the forward vector (the vector pointing forward with respect to the camera)
+ `vec3 camera_getUp(Camera* c)`: returns the up vector (the vector pointing up with respect to the camera)
+ `vec3 camera_getRight(Camera* c)`: returns the right vector (the vector pointing right with respect to the camera)

+ `vec3 camera_getBackward(Camera* c)`: returns the backward vector (the vector pointing backward with respect to the camera)
+ `vec3 camera_getDown(Camera* c)`: returns the down vector (the vector pointing down with respect to the camera)
+ `vec3 camera_getLeft(Camera* c)`: returns the left vector (the vector pointing left with respect to the camera)

**MATRIX**
+ `void camera_getViewMatrix(Camera* c)`: calculates the view matrix for the given camera and returns it

#### Renderer [#](#table-of-contents)
The renderer module can be used to render meshed, enable shaders and have rapid access to some OpenGL functions.

+ `void renderer_setGLClearColor(float r, float g, float b, float a)`: sets the clear color with RGBA values (default color is white (1, 1, 1, 1))
+ `void renderer_setGLPolygonMode(unsigned int mode)`: sets GL polygon mode (either to GL_POINT, GL_LINE or GL_FILL (default one))
+ `void renderer_setGLCullMode(unsigned int mode)`: sets GL cull mode (either to GL_FRONT, GL_BACK (default), GL_FRONT_AND_BACK or -1 (disable face culling))
+ `void renderer_setGLDepthTest(unsigned int depthFunction)`: sets GL depth test function.\
The fragments depth value goes from 0.0 (near) to 1.0 (far), meaning GL_LESS should be the go-to depth testing function when not changing the projection matrix provided by G3CE.\
KEEP IN MIND THAT IF YOU CHANGE THE PROJECTION MATRIX YOU COULD HAVE REVERSED / CHANGED THE NEAR - FAR FRAGMENT DEPTH VALUE MAPPING.\
The `depthFunction` parameter can either be:
`GL_ALWAYS`     =    The depth test always passes (same as disabling the depth test, the objects get rendered in the order they are rendered in code)
`GL_NEVER`      =    The depth test never passes
`GL_LESS`   	=    Passes if the fragment's depth value is less than the stored depth value
`GL_EQUAL`  	=    Passes if the fragment's depth value is equal to the stored depth value
`GL_LEQUAL`     =    Passes if the fragment's depth value is less than or equal to the stored depth value
`GL_GREATER`    =    Passes if the fragment's depth value is greater than the stored depth value
`GL_NOTEQUAL`   =    Passes if the fragment's depth value is not equal to the stored depth value
`GL_GEQUAL`     =    Passes if the fragment's depth value is greater than or equal to the stored depth value
`0`             =    Disables OpenGL depth test

+ `void renderer_useShader(unsigned int shader)`: uses a shader.\
**Parameters:**
    - shader (*unsigned int*): the shader program id
+ `void renderer_bindTexture(unsigned int texture, unsigned int unit)`: binds a texture.\
**Parameters:**
    - texture (*unsigend int*): the texture id
    - unit (*unsigend int*): the texture unit to bind the texture to
+ `void renderer_useCamera(Camera* camera)`: uses a camera.\
**Parameters:**
    - camera (Camera*): the pointer to the camera to use
+ `void renderer_prepare()`: prepares for rendering (automatically updates the view matrix is a camera and a shader with a view matrix uniform are being currently used)
+ `void renderer_renderMesh(Mesh* mesh)`: renders a given mesh.\
**Parameters:**
    - mesh (*Mesh**): the mesh pointer
+ `void renderer_renderObject(Object* object)`: renders the given object using the shader assigned to the object via object_assignShader() (or the currently active one if the assigned shader is 0)

#### Shader [#](#table-of-contents)
Shaders are the GPU code that allows you to render anything on the screen. They are written in GLSL (GL Shading Language). With this module you can easily load them in code and use them when rendering.
+ `unsigned int shader_create(char* vertexPath, char* fragmentPath)`: creates a shader program from the given vertex and fragment shader codes ("./file" means it is in "g3ce") and returns its program ID
+ `void shader_destroy(unsigned int programID)`: destroys the given shader
**Shader uniforms**
Uniforms are values you can manually transfer from the CPU to the GPU at runtime. Using the following functions, you can transfer boolean, floating point, integer values as well as vectors and matrices
+ `bool shader_hasUniform(const unsigned int programID, const char* name)`: returns true if the given shader has a uniform with the given name, false othewrise
+ `void setBoolean(const unsigned int programID, const char* name, bool value)`: sets boolean uniform
+ `void setFloat(const unsigned int programID, const char* name, float value)`: sets float uniform
+ `void setInteger(const unsigned int programID, const char* name, int value)`: sets integer uniform
+ `void setFloat2(const unsigned int programID, const char* name, vec2 value)`: sets float vector 2 uniform
+ `void setInteger2(const unsigned int programID, const char* name, int value[2])`: sets int vector 2 uniform
+ `void setFloat3(const unsigned int programID, const char* name, vec3 value)`: sets float vector 3 uniform
+ `void setInteger3(const unsigned int programID, const char* name, int value[3])`: sets int vector 3 uniform
+ `void setFloat4(const unsigned int programID, const char* name, vec4 value)`: sets float vector 4 uniform
+ `void setInteger4(const unsigned int programID, const char* name, int value[4])`: sets int vector 4 uniform
+ `void shader_setMatrix2(const unsigned int programID, const char* name, mat2 value)`: sets 2x2 float matrix uniform.\
YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER, so remember to call renderer_useShader(int shader) first!
+ `void shader_setMatrix3(const unsigned int programID, const char* name, mat3 value)`: sets 3x3 float matrix uniform.\
YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER, so remember to call renderer_useShader(int shader) first!
+ `void shader_setMatrix4(const unsigned int programID, const char* name, mat4 value)`: sets 4x4 float matrix uniform.\
YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER, so remember to call renderer_useShader(int shader) first!

**Remember: a shader must always be destroyed when not used anymore!**

#### Mesh [#](#table-of-contents)
With the mesh module, you can easily create simple meshes starting from vertices, indices and a draw mode.
After creating a mesh you can easily draw the mesh using a certain shader.
+ `Mesh mesh_new(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize, unsigned int vertexLength, unsigned int drawMode)`: creates a stack allocated mesh and returns it. This does not need to be destroyed
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
#include "engine/math/transform.h"
#include "engine/math/linal.h"
#include "engine/math/camera.h"
#include "engine/gfx/mesh.h"
#include "engine/gfx/renderer.h"
#include "engine/gfx/shader.h"
#include "engine/gfx/texture.h"
#include "engine/utils/console.h"

// you can also declare those four functions in a "main.h" file for good practice
void main_init();
void main_tick();
void main_draw();
void main_exit();
void on_resize();

int main() {
    // create the app
    app_create(800, 600, "My GLFW Window", 1);

    // app setup
    renderer_setGLClearColor(1, 1, 1, 1);
    renderer_setGLCullMode(GL_BACK);
    renderer_setGLDepthTest(GL_LESS);
    
    // main app loop
    app_loop(main_init, main_tick, main_draw, main_exit, on_resize);
    // close the app when the loop is broken (you can break out of the loop ONLY by calling app_requestClose())
    app_terminate();
    
    return 0;
}

unsigned int shader;
unsigned int texture;
Object* cube;
Camera* camera;

mat4 projectionMatrix;

// init function (called before entering the app main loop)
void main_init() {
    // create shaders
    shader = shader_create("./assets/shaders/texture_vertex.glsl", "./assets/shaders/texture_fragment.glsl");
    renderer_useShader(shader);
    shader_setInteger(shader, "texture", 0); // bind the texture unit 0

    // create a cube
    float vertices[] = {
        // front face
        // position            // color                    UVs
        -0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,       // 0
         0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 0.0f,       // 1
         0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,       // 2
        -0.5f,  0.5f, 0.5f,    1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f,       // 3

        // top face
        // position            // color                    UVs
        -0.5f, 0.5f, 0.5f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f,       // 4
         0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f,       // 5
         0.5f, 0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,       // 6
        -0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f,       // 7

        // right face
        // position            // color                    UVs
         0.5f, -0.5f, 0.5f,    1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f,       // 8
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f,       // 9
         0.5f, 0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,       // 10
         0.5f, 0.5f, 0.5f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f,       // 11

        // bottom face
        // position            // color                    UVs
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f,       // 12
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f,       // 13
         0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,       // 14
        -0.5f, -0.5f, 0.5f,    1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f,       // 15

        // left face
        // position            // color                    UVs
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f,       // 16
        -0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f,       // 17
        -0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,       // 18
        -0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f,       // 19

        // back face
        // position            // color                    UVs
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f,       // 20
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f,       // 21
        -0.5f, 0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f,       // 22
         0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f,       // 23
    };

    unsigned int indices[] = {
        // front face
        0, 1, 2,
        0, 2, 3,
        
        // top face
        4, 5, 6,
        4, 6, 7,

        // right face
        8, 9, 10,
        8, 10, 11,

        // bottom face
        12, 13, 14,
        12, 14, 15,

        // left face
        16, 17, 18,
        16, 18, 19,

        // back face
        20, 21, 22,
        20, 22, 23
    };
    
    // setup camera
    camera = camera_create();
    camera->position.z = 3.0f;
    renderer_useCamera(camera);
    // camera_setRotation(camera, -30, 45, 0); // enable this when orthographic projection is on to have isometric view

    texture = texture_create("./assets/textures/wall.jpg", false);

    // create a mesh
    // Mesh* mesh = mesh_create(vertices, sizeof(vertices), indices, sizeof(indices), 3+4+2, GL_TRIANGLES);
    Mesh mesh = mesh_new(vertices, sizeof(vertices), indices, sizeof(indices), 3+4+2, GL_TRIANGLES);
    mesh_registerVertexAttribute(&mesh, 0, 3); // position attribute
    mesh_registerVertexAttribute(&mesh, 1, 4); // color attribute
    mesh_registerVertexAttribute(&mesh, 2, 2); // uv attribute
    mesh_assignTexture(&mesh, texture, 0);

    // create the cube object
    cube = object_create(mesh);
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

    // change mesh transform and camera transform
    vec3 frontMotion = vec3_zero();
    vec3 sideMotion = vec3_zero();
    vec3 upMotion = vec3_zero();
    if (input_isKeyDown(GLFW_KEY_W)) frontMotion = camera_getForward(camera);
    if (input_isKeyDown(GLFW_KEY_A)) sideMotion = camera_getLeft(camera);
    if (input_isKeyDown(GLFW_KEY_S)) frontMotion = camera_getBackward(camera);
    if (input_isKeyDown(GLFW_KEY_D)) sideMotion = camera_getRight(camera);
    if (input_isKeyDown(GLFW_KEY_SPACE)) upMotion = camera_getUp(camera);
    if (input_isKeyDown(GLFW_KEY_LEFT_SHIFT)) upMotion = camera_getDown(camera);

    // combine the two movement vectors
    vec3 move = vec3_sum(frontMotion, sideMotion);
    move = vec3_sum(move, upMotion);
    // normalize the vector to avoid moving faster when moving on more than one axis
    move = vec3_normalize(move);

    // make the vector magnitude go to the maximum speed (in this case 0.1f);
    move = vec3_scale(move, 0.1f);

    // camera motion speed is 0.1 units per tick
    camera_moveByVector(camera, move);

    // camera rotation speed is 1.5 degrees per tick
    if (input_isKeyDown(GLFW_KEY_LEFT)) camera_rotate(camera, 0, 1.5f, 0);
    if (input_isKeyDown(GLFW_KEY_RIGHT)) camera_rotate(camera, 0, -1.5f, 0);
    if (input_isKeyDown(GLFW_KEY_UP)) camera_rotate(camera, 1.5f, 0, 0);
    if (input_isKeyDown(GLFW_KEY_DOWN)) camera_rotate(camera, -1.5f, 0, 0);

    if (input_isKeyPressed(GLFW_KEY_F1)) {
        // toggle, meybe preserve the gl modes in globals.h to access them later?
        if (input_isKeyDown(GLFW_KEY_RIGHT_SHIFT)) renderer_setGLPolygonMode(GL_LINE);
        else renderer_setGLPolygonMode(GL_FILL);
    }
}

// draw function (called once every frame, here you should put all you rendering code)
void main_draw() {
    // renderer_prepare(); // called by renderer_renderObject()
    // YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER!!!
    // upload the updated matrices
    shader_setMatrix4(shader, "projection", projectionMatrix);
    
    renderer_renderObject(cube);
}

// exit function (called after breaking out from the app main loop, before terminating the app)
void main_exit() {
    // mesh_destroy(mesh);
    object_destroy(cube);
    // texture_destroy(texture); // no need for this as it is assigned to the cube object that is freed when calling object_destroy()
    shader_destroy(shader);
    // transform_destroy(transform);
    camera_destroy(camera);
}

// resize function (called once at the start after the main_init() call and once every time a window resize event occurs)
void on_resize() {
    // calculate the projection matrix (recalculte on window size change and fov change)
    projectionMatrix = matrix_getPerspectiveProjection(
        window_getWidth(),
        window_getHeight(),
        70.0f, 0.1f, 100.0f
    );
    // projectionMatrix = matrix_getOrthographicProjection(
    //     -window_getWidth() / 2,
    //     window_getWidth() / 2,
    //     -window_getHeight() / 2,
    //     window_getHeight() / 2,
    //     -1000.0f, 1000.0f
    // );
}
```

Here is also the shader code:\
**Vertex shader:**
```GLSL
#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iCol;
layout (location = 2) in vec2 iUV;

out vec4 oCol;
out vec2 oUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(iPos, 1.0);
    oCol = iCol;
    oUV = iUV;
}
```

**Fragment shader:**
```GLSL
#version 330 core

in vec4 oCol;
in vec2 oUV;

out vec4 fragColor;

uniform bool debug_depth;
uniform sampler2D texture;

void main() {
    vec4 outputColor;
    if (debug_depth) {
        outputColor = vec4(vec3(gl_FragCoord.z), 1.0);
    } else {
        outputColor = texture2D(texture, oUV) * oCol;
    }
    fragColor = outputColor;
}
```

### Some theory and explainations [#](#table-of-contents)
The theory behind the perspective rendering done in `main.c` can be explained breaking it down in the following smaller and simpler steps:
1. Defining the cube
2. Placing the cube in the world
3. Creating a camera
4. Applying perspective rules

#### 1. Defining the mesh
A mesh is a collection of vertices connected in a precise order.\
A vertex is a collection of data (e.g.: position, color, texture coordinate, etc...).\
In G3CE you can define a mesh with the mesh_create() function.\
The mesh vertices positions are the location in space of the vertices relative to the mesh origin.\
This means that when defining a mesh we are working in the so called "local space", where the orgin is the center of your mesh.

#### 2. Placing the cube in the world
Our cube will be positioned somewhere in the virtual world. This is when the transform object comes in handy.\
The transform holds a position, a rotation and a scaling. You can modify those values as you want.

Now, in order to actually move, rotate and scale our mesh in the world we must apply the transformations to the mesh vertices.
A transformation is a mathematical operation that, given a vector (in our case all the vertex position), returns a new vector (all the new vertex position).

Transformations can be represented with matrices, which are tables of numbers arrenged in a specific order, following a precise logic.

This means we can have for example a translation matrix, which, when applied to a position vector changes it by a specific amount, embedded in the matrix itself, thus virtually "moving" the point represented by that vector (and so the whole mesh if we perform this operation for all of its vertices).
The same can be said for a rotation matrix and a scaling matrix.

Now, to apply a transformation we must multiply the corresponding matrix by the vector we want to transform, remembering that the **transformations are applied in reverse relatively to the matrix multiplication order** (matrix muliplication is not commutative).

So for example, we can have a translation matrix $T$, a rotation matrix $R$ and a vertex position represente by the vector $\vec{v}$. To apply the rotation before the translation we first combine the transformations into a new matrix $M$:
$$ M = T \cdot R $$
And then we get take the transformed vector by applying the combined transformation to the vector:
$$ \vec{v'} = M \cdot \vec{v} $$

Now, this might seem hard at first, but even reading it a second time could make it clearer, so give it a try.\
In any case, you won't be dealing too much with all of this, as G3CE automatically handles most of this transformation math for you.

However here comes the really important part: the previously cited $M$ matrix is an example of a **MODEL MATRIX**, which is the matrix that let's us go from the **local space** (where vertices positions are defined relatively to the mesh origin) to the **world space** (where vertices positions are defined relatively to the world origin).\
This is foundamental as we are essentially taking the mesh we've built before and now we are placing it in the world where and how we want it.

As you can imagine at this point, the model matrix depends on the transform position, rotation and scale, and G3CE has a built-in function that build the model matrix for you.\
The only thing you have to do as this point is to simply take the model matrix from the transform and assign it to the proper uniform value in the default shader.
This is exactly what is happening here
```C
void main_draw() {
    mat4 modelMatrix = transform_getModelMatrix(transform);
    shader_setMatrix4(shader, "model", modelMatrix);
}
```

#### 3. Creating a camera
Now that we know how transformations work understanding the camera can be even easier!\
The camera position and rotation can be thought as transformations too.\
We can thus build the corresponding transformation matrix which is also known as **view matrix**.\

At this point we should ask ourselves two questions:
1. How does the camera actually see?
2. Why is it called view matrix?

Let's answer these questions.

**1. The camera does not really see the world.**\
OpenGL will render whatever is found into a certain volume, called a **frustum**. Every vertex inside the frustum is projected onto a plane (your screen) according to some projection rules (see the next chapter).

So in order to move around the world we just need to move the frustum in the world to include or exclude the objects from our view.\
We can easily imagine a camera moving in the world and the relative frustum attached to it that moves accordingly.

Now we can't really move the frustum around the virtual world, but we can do the opposite: we can move the world around the frustum.\
And in reality is the world that moves in reverse relatively to the camera.

So if we position the camera (frustum) at (3, 0, 0) we can in fact move the entire world (translate all the meshes that populate it) by (-3, 0, 0).

The **key idea** to understand all of this is that from the camera perspective it is indifferent whether we move the camera back by 3 units or we move the world forward by 3 units.

By this point, it should be clear that to move the world we can apply a transformation matrix to all its meshes, but how do we build this matrix?

**2. The reason behind the name "view matrix"**\
This is where the **view matrix** plays its role.\
After placing the objects in the world via the **model matrix**, we can, as said before, move and rotate it in reverse relatively to the camera position and rotation.

How to apply these transformations?\
Using a matrix of course: the **view matrix**.

The **view matrix** transforms the world so that **everything is positioned as the camera views it**, thus the name "view matrix".

To build such a matrix we simply negate the camera position and rotation angles and move make a matrix out of that.\
Again, don't worry, G3CE builds the view matrix for you. You just have to move and rotate the camera, and to assign the view matrix to the shader uniform variable.
```C
void main_draw() {
    // ...
    mat4 viewMatrix = camera_getViewMatrix(camera);
    shader_setMatrix4(shader, "view", viewMatrix);
}
```

#### 4. Applying perspective rules
Finally we should specify how we project the vertices on the plane.

There are plenty of ways and technically there is no limit to how we project the vertices, but the ones that make more sense to us are the orthographic and the perspective projections.

**Orthographic projection**\
The projection lines are in this case parallel to eachother, so object keep their size regardless of their distance from the viewer.

**Perspective projection**\
This is the projection we are the most familiar with, as it is how our eyes and brains percieve the world.\
In this case objects shrink as they get farther from the viewer, because the vertices are projected with lines that converge to a single point (the "center of projection").

As you may imagine at this point, G3CE has a function to retrieve such matrices in a fast and simple way, so that you just have to set the proper uniform shader value to apply the projection rules you want.
```C
void main_draw() {
    // ...
    // perspective projection
    // this will use a frustum view volume, giving the illusion of perspective
    projectionMatrix = matrix_getPerspectiveProjection(
        window_getWidth(),
        window_getHeight(),
        70.0f, 0.1f, 100.0f
    );
    // orthographic projection
    // this will use a box view volume and everithing outside
    // of said bounds will be clipped and not rendered
    // remember to scale and position the objects accordingly
    projectionMatrix = matrix_getOrthographicProjection(
        -window_getWidth() / 2,
        window_getWidth() / 2,
        -window_getHeight() / 2,
        window_getHeight() / 2,
        -1000.0f, 1000.0f
    );
    shader_setMatrix4(shader, "projection", projectionMatrix);
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

A special mention and a super special thanks goes to the amazing people behind https://learnopengl.com/, who by making this knowledge free to access, also made this project possible.

### Version history [#](#table-of-contents)
+ **v1.0 b16092025-1:** created object implementation
+ **v1.0 b16092025-0:** implemented perspective and orthographic rendering via shaders, refined documentation (`README.md` file), fixed a couple bugs and typos here and there
+ **v1.0 b13092025-1:** added transform and camera objects
+ **v1.0 b13092025-0:** added linear algebra module
+ **v1.0 b12092025-0:** added 2D texture support
+ **v1.0 b11092025-0:** improved mesh implementation, added a renderer module to easily deals with some OpenGL functions
+ **v1.0 b08092025-0:** implemented shader uniform handling, fixed offset in vertex attribute location registration
+ **v1.0 b06092025-0:** implemented shader and mesh utilities
+ **v1.0 b01092025-0:** implemented functions for app handling, window and input

### About [#](#table-of-contents)
Made by G3Dev\
v1.0 b16092025-1
