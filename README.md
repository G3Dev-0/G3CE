# G3CE
This is an OpenGL engine useful for running simulations, creating games and general purpose rendering.\
**G3CE** stands for "**G3**Dev's **C** **E**ngine".

## Table of Contents
+ [**Using G3CE**](#using-g3ce)
+ [**Engine modules**](#engine-modules)
    - [**App**](#app)
    - [**Window**](#window)
    - [**Input**](#input)
    - [**Console**](#console)
+ [**Used technologies**](#used-technologies)
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
Home page: https://glad.dav1d.de/

- **GLFW**\
Window context and input handler\
Home page: https://www.glfw.org/

## About
Made by G3Dev\
v1.0 b01092025-0
