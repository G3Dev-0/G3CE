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

#include "main.h"

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

unsigned int vao;
unsigned int shader;
unsigned int texture;
Mesh* mesh;
Transform* transform;
Camera* camera;

mat4 projectionMatrix;
mat4 viewMatrix;
mat4 modelMatrix;

// init function (called before entering the app main loop)
void main_init() {
    // create shaders
    shader = shader_create("./assets/shaders/texture_vertex.glsl", "./assets/shaders/texture_fragment.glsl");
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
    // camera_setRotation(camera, -30, 45, 0); // enable this when orthographic projection is on to have isometric view

    // object position via transform
    transform = transform_create();
    transform_setScale(transform, 200, 200, 200);

    texture = texture_create("./assets/textures/wall.jpg", false);

    // create a mesh
    mesh = mesh_create(vertices, sizeof(vertices), indices, sizeof(indices), 3+4+2, GL_TRIANGLES);
    mesh_registerVertexAttribute(mesh, 0, 3); // position attribute
    mesh_registerVertexAttribute(mesh, 1, 4); // color attribute
    mesh_registerVertexAttribute(mesh, 2, 2); // uv attribute
    mesh_assignTexture(mesh, texture, 0);
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

    // recalculate the view and model matrices
    viewMatrix = camera_getViewMatrix(camera);
    modelMatrix = transform_getModelMatrix(transform);

    if (input_isKeyPressed(GLFW_KEY_F1)) {
        // toggle, meybe preserve the gl modes in globals.h to access them later?
        if (input_isKeyDown(GLFW_KEY_RIGHT_SHIFT)) renderer_setGLPolygonMode(GL_LINE);
        else renderer_setGLPolygonMode(GL_FILL);
    }
}

// draw function (called once every frame, here you should put all you rendering code)
void main_draw() {
    // TODO: add a UI renderer that has functions like write (text rendering) and shape rendering (like draw line, draw rect and draw circle)
    renderer_useShader(shader);
    // YOU CAN UPLOAD UNIFORMS ONLY WHEN USING THE SHADER!!!
    // upload the updated matrices
    shader_setMatrix4(shader, "projection", projectionMatrix);
    shader_setMatrix4(shader, "view", viewMatrix);
    shader_setMatrix4(shader, "model", modelMatrix);

    // renderer_bindTexture(texture, 0); // binding the texture to texture unit 0 (the active one by default)
    renderer_renderMesh(mesh);
}

// exit function (called after breaking out from the app main loop, before terminating the app)
void main_exit() {
    mesh_destroy(mesh);
    texture_destroy(texture);
    shader_destroy(shader);
    transform_destroy(transform);
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
    projectionMatrix = matrix_getOrthographicProjection(
        -window_getWidth() / 2,
        window_getWidth() / 2,
        -window_getHeight() / 2,
        window_getHeight() / 2,
        -1000.0f, 1000.0f
    );
}