#include "engine/app.h"
#include "engine/core/window.h"
#include "engine/core/input.h"
#include "engine/utils/console.h"

#include "main.h"

int main() {
    // create the app
    app_create(800, 600, "My GLFW Window", 1);
    // main app loop
    app_loop(main_init, main_tick, main_draw, main_exit);
    // close the app when the loop is broken (you can break out of the loop ONLY by calling app_requestClose())
    app_terminate();
    
    return 0;
}

// init function (called before entering the app main loop)
void main_init() {
    
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
    
}

// exit function (called after breaking out from the app main loop, before terminating the app)
void main_exit() {
    
}