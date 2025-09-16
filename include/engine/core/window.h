/*
WINDOW:
Window handling with GLFW and OpenGL initialization with GLAD
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include <GLFW/glfw3.h>

// creates the window with given parameters
GLFWwindow* window_create(int width, int height, char* title, bool resizable);
// destroyes the window
void window_destroy();

// WINDOW CUSTOMIZATION
// sets window title
void window_setTitle(char* title);
// sets window size
void window_setSize(int width, int height);
// sets window icon
void window_setIcon(char* filename);
// sets window fullscreen/windowed mode
void window_setFullscreen(bool fullscreen);

// toggles window fullscreen/windowed mode
void window_toggleFullscreen();

// returns the window width
float window_getWidth();
// returns the window height
float window_getHeight();

#endif