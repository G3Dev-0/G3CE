/*
CAMERA:
Holds all camera related functions (basically more matrix math!)
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "engine/math/linal.h"

typedef struct {
    vec3 position;
    vec3 rotation;
} Camera;

// creates a camera positioned at the world origin (0, 0, 0)
// and looking forward with rotation angles all set to zero
// REMEMBER you MUST DESTROY the camera via camera_destroy()!
Camera* camera_create();
// destroys the given camera
void camera_destroy(Camera* c);

// SETTERS
// sets the given camera position to the given coordinates values
void camera_setPosition(Camera* c, float x, float y, float z);
// sets the given camera position to the given pitch, yaw and roll values
void camera_setRotation(Camera* c, float pitch, float yaw, float roll);

// OPERATIONS
// moves the given camera by the given move vector
void camera_moveByVector(Camera* c, vec3 move);
// moves the given camera by the given motion values
void camera_move(Camera* c, float xm, float ym, float zm);
// rotates the camera by the given rotation vector
void camera_rotateByVector(Camera* c, vec3 rotation);
// rotates the camera by the given angles
void camera_rotate(Camera* c, float xr, float yr, float zr);

// CAMERA COORDINATE SYSTEM
// returns the x axis direction of the camera centered coordinate system
vec3 camera_getPositiveX(Camera* c);
// returns the y axis direction of the camera centered coordinate system
vec3 camera_getPositiveY(Camera* c);
// returns the z axis direction of the camera centered coordinate system
vec3 camera_getPositiveZ(Camera* c);

// returns the forward vector (the vector pointing forward with respect to the camera)
vec3 camera_getForward(Camera* c);
// returns the up vector (the vector pointing up with respect to the camera)
vec3 camera_getUp(Camera* c);
// returns the right vector (the vector pointing right with respect to the camera)
vec3 camera_getRight(Camera* c);

// returns the backward vector (the vector pointing backward with respect to the camera)
vec3 camera_getBackward(Camera* c);
// returns the down vector (the vector pointing down with respect to the camera)
vec3 camera_getDown(Camera* c);
// returns the left vector (the vector pointing left with respect to the camera)
vec3 camera_getLeft(Camera* c);

// calculates the view matrix for the given camera and returns it
mat4 camera_getViewMatrix(Camera* c);

#endif