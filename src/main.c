#include "engine/app.h"
#include "engine/core/window.h"
#include "engine/core/input.h"
#include "engine/gfx/mesh.h"
#include "engine/gfx/renderer.h"
#include "engine/gfx/shader.h"

#include "main.h"

int main() {
    // create the app
    app_create(800, 600, "My GLFW Window", 1);

    // app setup
    renderer_setGLClearColor(1, 1, 1, 1);

    // main app loop
    app_loop(main_init, main_tick, main_draw, main_exit);
    // close the app when the loop is broken (you can break out of the loop ONLY by calling app_requestClose())
    app_terminate();
    
    return 0;
}

int vao;
int shader;
Mesh* mesh;

// init function (called before entering the app main loop)
void main_init() {
    // create a shader
    shader = shader_create("./assets/shaders/color_vertex.glsl", "./assets/shaders/color_fragment.glsl");

    float positions[9] = {
        0.0, 0.5, 0.0,
        -0.5, 0.0, 0.0,
        0.5, 0.0, 0.0
    };

    float colors[12] = {
        1.0, 0.5, 0.0, 0.0,
        0.5, 0.0, 1.0, 0.0,
        0.5, 1.0, 0.5, 0.0
    };

    unsigned int indices[3] = {
        0, 1, 2
    };

    // create a mesh
    mesh = mesh_create(positions, sizeof(positions), indices, sizeof(indices), GL_TRIANGLES);
    mesh_addVertexAttributeFloat(mesh, 1, 4, colors, sizeof(colors));
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
    mesh_draw(mesh, shader); // todo: maybe move draw_mesh in renderer
    //TODO: add a UI renderer that has functions like write (text rendering) and shape rendering (like draw line, draw rect and draw circle)
}

// exit function (called after breaking out from the app main loop, before terminating the app)
void main_exit() {
    mesh_destroy(mesh);
    shader_destroy(shader);
}