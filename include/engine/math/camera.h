/*
CAMERA:
Holds all camera related functions (basically more matrix math!)
*/

#ifndef CAMERA_H
#define CAMERA_H

/*
There should be:

pos, pitch, yaw // set as globals? there could be a better solution, maybe a struct held in the heap...so basically just a smaller transform module

get_viewMatrix() // constantly called every frame to update the camera position
*/

#include "engine/math/linal.h"

typedef struct {
    vec3 position;
    float pitch, yaw;
} Camera;

// creates a camera positioned at the world origin (0, 0, 0)
// and looking forward with pitch and yaw angles both set to zero
// REMEMBER you MUST DESTROY the camera via camera_destroy()!
Camera* camera_create();
// destroys the given camera
void camera_destroy(Camera* c);

// OPERATIONS
// moves the given camera by the given move vector
void camera_move(Camera* c, vec3 move);
// rotates the camera by the given angles
void camera_rotate(Camera* c, float xr, float yr);

// calculates the view matrix for the given camera and returns it
void camera_getViewMatrix(Camera* c);

#endif