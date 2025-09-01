/*
INPUT:
Input handling
*/

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <GLFW/glfw3.h>

// GLFW callbacks
void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// KEYBOARD
// returns true ONLY the first tick the key is pressed, then it returns false
bool input_isKeyPressed(int key);
// returns true EVERY tick the key is pressed, returns false if the key is not pressed
bool input_isKeyDown(int key);
// returns true ONLY the first tick the key is released, then it returns false
bool input_isKeyReleased(int key);

// MOUSE
// returns true ONLY the first tick the button is pressed, then it returns false
bool input_isButtonPressed(int button);
// returns true EVERY tick the button is pressed, returns false if the button is not pressed
bool input_isButtonDown(int button);
// returns true ONLY the first tick the button is released, then it returns false
bool input_isButtonReleased(int button);

// returns the mouse x position in the window (0 to window_width - 1 from LEFT to RIGHT)
double input_getMouseX();
// returns the mouse y position in the window (0 to window_height - 1 from TOP to BOTTOM)
double input_getMouseY();
// returns the mouse scroll (0 when not scrolling, NEGATIVE when scrolling DOWNWARDS, POSITIVE when scrolling UPWARDS)
int input_getMouseScroll();

#endif