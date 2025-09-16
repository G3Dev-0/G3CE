/*
WINDOW:
Window handling with GLFW and OpenGL initialization with GLAD
*/

//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stbi/stb_image.h>

#include "engine/core/input.h"
#include "engine/utils/console.h"

#include "engine/globals.h" // to use the window pointer

#include "engine/core/window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// used for fullscreen-windowed mode switching
int window_width, window_height, window_xpos, window_ypos;
bool is_fullscreen;

// creates the window with given parameters
GLFWwindow* window_create(int width, int height, char* title, bool resizable) {
    // initialize GLFW
    glfwInit();
    // set some GLFW flags
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    
    glfwWindowHint(GLFW_RESIZABLE, resizable);
    
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    // create the window
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        console_error("Failed to create GLFW window");
        window_destroy();
        return NULL;
    }

    // make context current (necessary to make OpenGL work)
    glfwMakeContextCurrent(window);

    // set GLFW window callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // initialise OpenGL variables manager
    
    // if using GLEW
    //glewInit();

    // if using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        console_error("Failed to load GLAD");
        return NULL;
    }

    // setting GLFW callbacks
    glfwSetCursorPosCallback(window, mouse_position_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);

    return window;
}

// destroyes the window
void window_destroy() {
    glfwTerminate();
}

// WINDOW CUSTOMIZATION
// sets window title
void window_setTitle(char* title) {
    glfwSetWindowTitle(window, title);
}

// sets window size
void window_setSize(int width, int height) {
    glfwSetWindowSize(window, width, height);
}

// sets window icon
void window_setIcon(char* filename) {
    // try loading the image
    int width, height, channels;    
    unsigned char* pixels = stbi_load(filename, &width, &height, &channels, 4);
    if (!pixels) {
        console_error("Failed to load window icon from file at \"%s\"", filename);
        return;
    }

    // create the glfw image structure
    GLFWimage image;
    image.width = width;
    image.height = height;
    image.pixels = pixels;
    
    // set the icon image as the window icon if successfully loaded the icon image
    glfwSetWindowIcon(window, 1, &image);

    // free the memory allocated to the image by stbi_load()
    stbi_image_free(pixels);
}

// sets window fullscreen/windowed mode
void window_setFullscreen(bool fullscreen) {
    if (fullscreen && !is_fullscreen) {
        // save the current window position and size (to set them again when switching back to windowed mode)
        glfwGetWindowPos(window, &window_xpos, &window_ypos);
        glfwGetWindowSize(window, &window_width, &window_height);
        
        // get primary monitor
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        // get video mode from primary monitor
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        
        // set the current video mode to match the monitor specifications, thus setting the window to go fullscreen
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        
        is_fullscreen = true;
    } else if (!fullscreen && is_fullscreen) {
        // go back to windowed mode by setting the previous (when it was in windowed mode) values for the current video mode
        glfwSetWindowMonitor(window, NULL, window_xpos, window_ypos, window_width, window_height, 0);

        // reset window position and window size
        glfwSetWindowPos(window, window_xpos, window_ypos);
        glfwSetWindowSize(window, window_width, window_height);
        
        is_fullscreen = false;
    }
}

// toggles window fullscreen/windowed mode
void window_toggleFullscreen() {
    if (is_fullscreen) window_setFullscreen(false);
    else window_setFullscreen(true);
}

// returns the window width
float window_getWidth() {
    int width;
    glfwGetWindowSize(window, &width, NULL);
    return (float) width;
}
// returns the window height
float window_getHeight() {
    int height;
    glfwGetWindowSize(window, NULL, &height);
    return (float) height;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // set OpenGL viewport
    glViewport(0, 0, width, height);

    FLAG_WINDOW_RESIZED = true;
}