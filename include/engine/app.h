/*
APP:
Contains all the app-related functions
*/

#ifndef APP_H
#define APP_H

#include <stdbool.h>

#include <GLFW/glfw3.h>

// creates the app with the given window parameters
void app_create(int width, int height, char* title, bool resizable);
// starts the app by running the given functions in a loop
void app_loop(void (*main_init)(), void (*main_tick)(), void (*main_draw)(), void (*main_exit)(), void (*on_resize)());
// requests the app to close, it CANNOT be called outside of the app main loop
void app_requestClose();
// closes the app by terminating GLFW
void app_terminate();

#endif