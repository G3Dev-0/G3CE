#include "engine/app.h"
#include "engine/core/window.h"
#include "engine/core/input.h"
#include "engine/gfx/mesh.h"
#include "engine/gfx/renderer.h"
#include "engine/gfx/shader.h"
#include "engine/gfx/texture.h"

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

unsigned int vao;
unsigned int shader;
unsigned int texture;
Mesh* mesh;

// init function (called before entering the app main loop)
void main_init() {
    // create shaders
    shader = shader_create("./assets/shaders/texture_vertex.glsl", "./assets/shaders/texture_fragment.glsl");
    shader_setInteger(shader, "texture", 0);    

    float vertices[] = {
        // position         // color                UVs
        -0.5, -0.5, 0.0,    1.0, 0.0, 0.0, 0.0,     0.0, 0.0,
         0.5, -0.5, 0.0,    0.0, 1.0, 0.0, 0.0,     1.0, 0.0,
         0.5,  0.5, 0.0,    0.0, 0.0, 1.0, 0.0,     1.0, 1.0,
        -0.5,  0.5, 0.0,    1.0, 1.0, 1.0, 0.0,     0.0, 1.0
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    texture = texture_create("./assets/textures/wall.jpg", false);

    // create a mesh
    // mesh = mesh_create(positions, sizeof(positions), indices, sizeof(indices), GL_TRIANGLES);
    // mesh_addVertexAttributeFloat(mesh, 1, 4, colors, sizeof(colors));
    mesh = mesh_create(vertices, sizeof(vertices), indices, sizeof(indices), 3+4+2, GL_TRIANGLES);
    mesh_registerVertexAttribute(mesh, 0, 3); // position attribute
    mesh_registerVertexAttribute(mesh, 1, 4); // color attribute
    mesh_registerVertexAttribute(mesh, 2, 2); // uv attribute
    // mesh_assignTexture(mesh, texture);
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
    //TODO: add a UI renderer that has functions like write (text rendering) and shape rendering (like draw line, draw rect and draw circle)
    renderer_useShader(shader);
    renderer_bindTexture(texture, 0);
    renderer_renderMesh(mesh);
}

// exit function (called after breaking out from the app main loop, before terminating the app)
void main_exit() {
    mesh_destroy(mesh);
    texture_destroy(texture);
    shader_destroy(shader);
}