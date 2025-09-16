/*
CAMERA:
Holds all camera related functions (basically more matrix math!)
*/

#include <stdlib.h>
#include <math.h>

#include "engine/math/linal.h"
#include "engine/utils/console.h"

#include "engine/math/camera.h"

// creates a camera positioned at the world origin (0, 0, 0)
// and looking forward with rotation angles all set to zero
// REMEMBER you MUST DESTROY the camera via camera_destroy()!
Camera* camera_create() {
    Camera* c = (Camera*) malloc(sizeof(Camera));
    if (c == NULL) {
        console_error("Failed to allocate memory for the camera");
        return NULL;
    }

    c->position = vec3_zero();
    c->rotation = vec3_zero();

    return c;
}
// destroys the given camera
void camera_destroy(Camera* c) {
    free(c);
}

// SETTERS
// sets the given camera position to the given coordinates values
void camera_setPosition(Camera* c, float x, float y, float z) {
    c->position.x = x;
    c->position.y = y;
    c->position.z = z;
}
// sets the given camera position to the given pitch, yaw and roll values
void camera_setRotation(Camera* c, float pitch, float yaw, float roll) {
    c->rotation.x = pitch;
    c->rotation.y = yaw;
    c->rotation.z = roll;
}

// OPERATIONS
// moves the given camera by the given move vector
void camera_moveByVector(Camera* c, vec3 move) {
    c->position.x += move.x;
    c->position.y += move.y;
    c->position.z += move.z;
}
// moves the given camera by the given motion values
void camera_move(Camera* c, float xm, float ym, float zm) {
    c->position.x += xm;
    c->position.y += ym;
    c->position.z += zm;
}
// rotates the camera by the given rotation vector
void camera_rotateByVector(Camera* c, vec3 rotation) {
    c->rotation.x += rotation.x;
    c->rotation.y += rotation.y;
    c->rotation.z += rotation.z;
}
// rotates the camera by the given angles
void camera_rotate(Camera* c, float xr, float yr, float zr) {
    c->rotation.x += xr;
    c->rotation.y += yr;
    c->rotation.z += zr;
}

// CAMERA COORDINATE SYSTEM
// returns the x axis direction of the camera centered coordinate system
vec3 camera_getPositiveX(Camera* c) {
    // by taking the world up vector (y axis versor)
    // and doing a cross product with the forward we get the camera right vector
    // (as you always get a vector perpendicular to both)
    vec3 worldUp = vec3_new(0, 1, 0);
    // be careful because cross product order matters
    // following the right hand rule we first put world up vector (right index finger),
    // then the the positive Z vector (right thumb) and we get the positive X vector
    // pointing to the right (right middle finger)
    // inverting the order would produce a positive X vector pointing to the negative X
    vec3 positiveX = vec3_cross(worldUp, camera_getPositiveZ(c));

    return positiveX;
}
// returns the y axis direction of the camera centered coordinate system
vec3 camera_getPositiveY(Camera* c) {
    // the camera positive Y vector is given by doing a
    // cross product between the camera forward and up vectors
    // (as you always get a vector perpendicular to both)

    // be careful because cross product order matters
    // following the right hand rule we first put the positive Z vector (right index finger),
    // then the positive X vector (right thumb) and we get the positive Y vector
    // pointing positive Y (right middle finger)
    // inverting the order would produce a positive Y vector pointing to the negative Y
    vec3 positiveY = vec3_cross(camera_getPositiveZ(c), camera_getPositiveX(c));

    return positiveY;
}
// returns the z axis direction of the camera centered coordinate system
vec3 camera_getPositiveZ(Camera* c) {
    // the positive z direction vector can be obtained through the spherical polar coordinates
    const float theta = c->rotation.x * DEGREES_TO_RADIANS;
    const float phi = c->rotation.y * DEGREES_TO_RADIANS;
    const float x = sinf(phi) * cosf(theta);
    const float y = -sinf(theta);
    const float z = cosf(phi) * cosf(theta);
    vec3 positiveZ = vec3_new(x, y, z);

    return positiveZ;
}

// returns the forward vector (the vector pointing forward with respect to the camera)
vec3 camera_getForward(Camera* c) {
    // the forward vector points in the opposite direction with respect to the camera positive Z vector
    return vec3_negate(camera_getPositiveZ(c), TARGET_ALL);
}
// returns the up vector (the vector pointing up with respect to the camera)
vec3 camera_getUp(Camera* c) {
    return camera_getPositiveY(c);
}
// returns the right vector (the vector pointing right with respect to the camera)
vec3 camera_getRight(Camera* c) {
    return camera_getPositiveX(c);
}

// returns the backward vector (the vector pointing backward with respect to the camera)
vec3 camera_getBackward(Camera* c) {
    return camera_getPositiveZ(c);
}
// returns the down vector (the vector pointing down with respect to the camera)
vec3 camera_getDown(Camera* c) {
    return vec3_negate(camera_getPositiveY(c), TARGET_ALL);
}
// returns the left vector (the vector pointing left with respect to the camera)
vec3 camera_getLeft(Camera* c) {
    return vec3_negate(camera_getPositiveX(c), TARGET_ALL);
}

// calculates the view matrix for the given camera and returns it
mat4 camera_getViewMatrix(Camera* c) {
    // translation in the negative camera position,
    // it's not the camera that moves in the world...
    // it's the world that revolves around the camera
    mat4 translationMatrix = mat4_translation(vec3_negate(c->position, TARGET_ALL));
    
    // use a quaternion based rotation system
    quat xRot = quat_rotation(vec3_new(1, 0, 0), -c->rotation.x);
    quat yRot = quat_rotation(vec3_new(0, 1, 0), -c->rotation.y);
    quat zRot = quat_rotation(vec3_new(0, 0, 1), -c->rotation.z);
    quat rotationQuat = quat_multiply(xRot, yRot);
    rotationQuat = quat_multiply(rotationQuat, zRot);
    // convert to rotation matrix
    mat4 rotationMatrix = quat_to_mat4(rotationQuat);
    // mat4 rotationMatrix = mat4_eulerRotation(vec3_new(-(c->pitch), -(c->yaw), 0));

    // translate first, then rotate
    // this is the right order as you should first translate the world
    // to the inverse of the camera position
    // because the rotation matrix always rotates around the origin,
    // meaning the world will now rotate pivoting around the camera position
    mat4 view = mat4_multiply(rotationMatrix, translationMatrix);

    return view;
}