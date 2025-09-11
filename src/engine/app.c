/*
APP:
Contains all the app-related functions
*/

#include "engine/core/window.h"
#include "engine/gfx/renderer.h"

#include "engine/app.h"

GLFWwindow* window;

// creates the app with the given window parameters
void app_create(int width, int height, char* title, bool resizable) {
    window = window_create(width, height, title, resizable);
}

// starts the app by running the given functions in a loop
void app_loop(void (*main_init)(), void (*main_tick)(), void (*main_draw)(), void (*main_exit)()) {
    main_init();

    while (!glfwWindowShouldClose(window)) {
        // input
        //processInput(window);

        // tick
        main_tick();

        // RENDER
        // clear
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        
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