/*
CAMERA:
Holds all camera related functions (basically more matrix math!)
*/

#include <stdlib.h>

#include "engine/utils/console.h"

#include "engine/math/camera.h"

// creates a camera positioned at the world origin (0, 0, 0)
// and looking forward with pitch and yaw angles both set to zero
// REMEMBER you MUST DESTROY the camera via camera_destroy()!
Camera* camera_create() {
    Camera* c = (Camera*) malloc(sizeof(Camera));
    if (c == NULL) {
        console_error("Failed to allocate memory for the camera");
        return NULL;
    }

    c->position = vec3_zero();
    c->pitch = 0;
    c->yaw = 0;
}
// destroys the given camera
void camera_destroy(Camera* c) {
    free(c);
}

// OPERATIONS
// moves the given camera by the given move vector
void camera_move(Camera* c, vec3 move) {
    c->position = vec3_sum(c->position, move);
}
// rotates the camera by the given angles
void camera_rotate(Camera* c, float xr, float yr) {
    c->pitch += xr;
    c->yaw += yr;
}

// calculates the view matrix for the given camera and returns it
void camera_getViewMatrix(Camera* c) {
    // translation in the negative camera position,
    // it's not the camera that moves in the world...
    // it's the world that revolves around the camera
    mat4 translationMatrix = mat4_translation(vec3_scale(c->position, -1));
    mat4 rotationMatrix = mat4_eulerRotation(vec3_new(-(c->pitch), -(c->yaw), 0));

    // rotate first, then translate
    mat4 view = mat4_multiply(translationMatrix, rotationMatrix);
}