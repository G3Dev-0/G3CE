/*
INPUT:
Input handling
*/

#include "engine/globals.h"

#include "engine/core/input.h"

// these are state control flags used for preventing pressed signal to be returned after the first press tick
bool first_key_press_tick_passed[255] = {false}; // 255 false values
bool can_release_key[255] = {false}; // 255 false values

bool first_button_press_tick_passed[5] = {false}; // 5 false values
bool can_release_button[5] = {false}; // 5 false values

// mouse input variables
double mouseX = 0.0;
double mouseY = 0.0;
double scroll = 0.0;

// GLFW callbacks
void mouse_position_callback(GLFWwindow* window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    scroll = yoffset;
}

// KEYBOARD
// returns true ONLY the first tick the key is pressed, then it returns false
bool input_isKeyPressed(int key) {
    if (glfwGetKey(window, key)) {
        // return pressed if the state control flag allows it
        if (!first_key_press_tick_passed[key]) {
            first_key_press_tick_passed[key] = true;
            return true;
        }
    // reset the key state control flag
    } else {
        first_key_press_tick_passed[key] = false;
    }
    return false;
}

// returns true EVERY tick the key is pressed, returns false if the key is not pressed
bool input_isKeyDown(int key) {
    if (glfwGetKey(window, key)) return true;
}

// returns true ONLY the first tick the key is released, then it returns false
bool input_isKeyReleased(int key) {
    if (!glfwGetKey(window, key)) {
        // return release if the state control flag allows it
        if (can_release_key[key]) {
            can_release_key[key] = false;
            return true;
        }
    // reset the key state control flag
    } else {
        can_release_key[key] = true;
    }
    return false;
}

// MOUSE
// returns true ONLY the first tick the button is pressed, then it returns false
bool input_isButtonPressed(int button) {
    if (glfwGetMouseButton(window, button)) {
        // return pressed if the state control flag allows it
        if (!first_button_press_tick_passed[button]) {
            first_button_press_tick_passed[button] = true;
            return true;
        }
    // reset the button state control flag
    } else {
        first_button_press_tick_passed[button] = false;
    }
    return false;
}

// returns true EVERY tick the button is pressed, returns false if the button is not pressed
bool input_isButtonDown(int button) {
    if (glfwGetMouseButton(window, button)) return true;
}

// returns true ONLY the first tick the button is released, then it returns false
bool input_isButtonReleased(int button) {
    if (!glfwGetMouseButton(window, button)) {
        // return release if the state control flag allows it
        if (can_release_button[button]) {
            can_release_button[button] = false;
            return true;
        }
    // reset the button state control flag
    } else {
        can_release_button[button] = true;
    }
    return false;
}

// returns the mouse x position in the window (0 to window_width - 1 from LEFT to RIGHT)
double input_getMouseX() {
    return mouseX;
}

// returns the mouse y position in the window (0 to window_height - 1 from TOP to BOTTOM)
double input_getMouseY() {
    return mouseY;
}

// returns the mouse scroll (0 when not scrolling, NEGATIVE when scrolling DOWNWARDS, POSITIVE when scrolling UPWARDS)
int input_getMouseScroll() {
    return scroll;
}