/*
TRANSFORM
This is the transform object.
It contains all the necessary functions and parameters to describe
an object position, rotation and scaling.
It essentially serves bridges the gap between local space and world space
*/

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "engine/math/linal.h"

typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Transform;

// creates a blank transform (posision and rotation are zero vectors, while scale is a one vector)
// REMEMBER: you MUST also DESTROY IT at the end via transform_destroy()!
Transform* transform_create();
// destroys the given transform object
void transform_destroy(Transform* t);

// SETTERS
// sets the given transform position to the given position values (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
void transform_setPosition(Transform* t, float x, float y, float z);
// sets the given transform rotation to the given rotation values
void transform_setRotation(Transform* t, float pitch, float yaw, float roll);
// sets the given transform scale to the given scale values
void transform_setScale(Transform* t, float xs, float ys, float zs);

// OPERATIONS
// increments the given transform position by the given translation vector (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
void transform_changePosition(Transform* t, vec3 translation);
// increments the given transform rotation by the given rotation vector (pitch, yaw, roll) (angles are in degrees)
void transform_changeRotation(Transform* t, vec3 rotation);
// increment the the given transform scale by the given scaling vector (xs, ys, zs)
void transform_changeScale(Transform* t, vec3 scaling);

// increments the given transform position by the given translation values (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
void transform_changePositionValues(Transform* t, float xm, float ym, float zm);
// increments the given transform rotation by the given rotation values (pitch, yaw, roll) (angles are in degrees)
void transform_changeRotationValues(Transform* t, float xr, float yr, float zr);
// increment the the given transform scale by the given scaling values (xs, ys, zs)
void transform_changeScaleValues(Transform* t, float xs, float ys, float zs);

// MATRIX
// calculates the model matrix for the given transform and returns it
mat4 transform_getModelMatrix(Transform* t);

#endif