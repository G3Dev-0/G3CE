/*
APP:
Contains all the app-related functions
*/

#include <stbi/stb_image.h>

#include "engine/core/window.h"
#include "engine/gfx/renderer.h"
#include "engine/globals.h"

#include "engine/app.h"

// // declare global variables here
// // FLAGS
// bool FLAG_WINDOW_RESIZED = false;
// // WINDOW
// GLFWwindow* window;

// creates the app with the given window parameters
void app_create(int width, int height, char* title, bool resizable) {
    window = window_create(width, height, title, resizable);
    stbi_set_flip_vertically_on_load(true); // vertically flip all the loaded textures for OpenGL
}

// starts the app by running the given functions in a loop
void app_loop(void (*main_init)(), void (*main_tick)(), void (*main_draw)(), void (*main_exit)(), void (*on_resize)()) {
    main_init();

    while (!glfwWindowShouldClose(window)) {
        // events
        // resize event
        if (FLAG_WINDOW_RESIZED) {
            on_resize();
            FLAG_WINDOW_RESIZED = false;
        }

        // tick
        main_tick();

        // RENDER
        // clear
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        main_draw();

        // finalize frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    main_exit();
}

// requests the app to close, it CANNOT be called outside of the app main loop
void app_requestClose() {
    // skip if close was already requested
    if (glfwWindowShouldClose(window)) return;

    // request window close
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// closes the app by terminating GLFW
void app_terminate() {
    glfwTerminate();
}