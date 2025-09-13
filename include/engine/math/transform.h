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

// // SETTERS
// // sets the given transform position
// void transform_setPosAll(Transform* t, float x, float y, float z);
// // sets the given transform position
// void transform_setPos(Transform* t, vec3 pos);
// // sets the given transform x position
// void transform_setPosX(Transform* t, float x);
// // sets the given transform y position
// void transform_setPosY(Transform* t, float y);
// // sets the given transform z position
// void transform_setPosZ(Transform* t, float z);

// // sets the given transform rotation
// void transform_setRotAll(Transform* t, float pitch, float yaw, float roll);
// // sets the given transform rotation
// void transform_setRot(Transform* t, vec3 rot);
// // sets the given transform x rotation
// void transform_setRotX(Transform* t, float pitch);
// // sets the given transform y rotation
// void transform_setRotY(Transform* t, float yaw);
// // sets the given transform z rotation
// void transform_setRotZ(Transform* t, float roll);

// // sets the given transform scale
// void transform_setScaleAll(Transform* t, float xs, float ys, float zs);
// // sets the given transform scale
// void transform_setScale(Transform* t, vec3 scale);
// // sets the given transform x scale
// void transform_setScaleX(Transform* t, float xs);
// // sets the given transform y scale
// void transform_setScaleY(Transform* t, float ys);
// // sets the given transform z scale
// void transform_setScaleZ(Transform* t, float zs);

// OPERATIONS
// increments the given transform position by the given translation vector (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
void transform_changePosition(Transform* t, vec3 translation);

// increments the given transform rotation by the given rotation vector (pitch, yaw, roll) (angles are in degrees)
void transform_changeRotation(Transform* t, vec3 rotation);

// increment the the given transform scale by the given scaling vector (xs, ys, zs)
void transform_changeScale(Transform* t, vec3 scaling);

// MATRIX
// calculates the model matrix for the given transform and returns it
mat4 transform_getModelMatrix(Transform* t);

#endif