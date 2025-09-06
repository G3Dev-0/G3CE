# G3CE
**G3**Dev's **C** **E**ngine is an OpenGL engine useful for running simulations, creating games and general purpose rendering.

## Table of Contents
+ [**Using G3CE**](#using-g3ce)
+ [**Engine modules**](#engine-modules)
    - [**App**](#app)
    - [**Window**](#window)
    - [**Input**](#input)
    - [**Console**](#console)
    - [**File**](#file)
    - [**Shader**](#shader)
    - [**Mesh**](#mesh)
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
+ `bool file_write(char* path, char* content)`: writes content to a file at path ("./file" means it is in "g3ge")
+ `char* file_read(char* path)`: returns the content of a file at path ("./file" means it is in "g3ge"), YOU MUST FREE THE RETURN VALUE by calling stdlib.free()!
+ `int file_remove(char* path)`: removes a file at path ("./file" means it is in "g3ge")

#### Shader [#](#table-of-contents)
Shaders are the GPU code that allows you to render anything on the screen. They are written in GLSL (GL Shading Language). With this module you can easily load them in code and use them when rendering.
+ `int shader_create(char* vertexPath, char* fragmentPath)`: creates a shader program from the given vertex and fragment shader codes ("./file" means it is in "g3ge") and returns its program ID
+ `void shader_use(int programID)`: activates the given shader
+ `void shader_destroy(int programID)`: destroys the given shader

**Remember: a shader must always be destroyed when not used anymore!**

#### Mesh [#](#table-of-contents)
With the mesh module, you can easily create simple meshes starting from vertices, indices and a draw mode.
After creating a mesh you can easily draw the mesh using a certain shader.
+ `Mesh* mesh_create(float* vertices, unsigned int verticesLength, unsigned int* indices, unsigned int indicesLength, int drawMode)`: creates the mesh and returns it\
Parameters:
    + **vertices:** the vertices position array
    + **verticesLength:** the sizeof() of the vertices position array
    + **indices:** the indices array, specifing the order in which to render the verices
    + **indicesLength:** the sizeof() of the indices array
    + **drawMode:** the OpenGL mode to draw the verices (GL_TRIANGLES, GL_QUADS, ...)

    YOU MUST FREE THE VAO BY CALLING mesh_destroy()
+ `void mesh_addVertexAttributeFloat(Mesh* mesh, int attribLocation, int size, float* data, unsigned int dataLength)`: creates a VBO and associates it to a vertex attribute of type int buffer to the specified mesh\
Parameters:
    + **attribLocatio:n** the location of the attribute in the shader
    + **size:** the number of components for each vertex attribute (e.g.: 3 for 3D position, 4 for RGBA colors)
    + **dataLength:** the sizeof() of the data array
+ `void mesh_destroy(Mesh* mesh)`: destroies the given mesh (VAO)
+ `void mesh_draw(Mesh* mesh, int shader)`: draws the given mesh using the given shader (programID)

**Remember: a mesh must always be destroyed when not used anymore!**

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

### Version history [#](#table-of-contents)
+ **v1.0 b01092025-0:** implemented functions for app handling, window and input
+ **v1.0 b06092025-0:** implemented shader and mesh utilities

### About [#](#table-of-contents)
Made by G3Dev\
v1.0 b01092025-0