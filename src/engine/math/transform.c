/*
TRANSFORM
This is the transform object.
It contains all the necessary functions and parameters to describe
an object position, rotation and scaling.
It essentially serves bridges the gap between local space and world space
*/

#include <stdlib.h>

#include "engine/utils/console.h"

#include "engine/math/transform.h"

// creates a blank transform (posision and rotation are zero vectors, while scale is a one vector)
// REMEMBER: you MUST also DESTROY IT at the end via transform_destroy()!
Transform* transform_create() {
    // dynamic allocation because the object will likely be there for a long time
    Transform* t = (Transform*) malloc(sizeof(Transform));
    if (t == NULL) {
        console_error("Failed to allocate memory for the transform");
        return NULL;
    }

    t->position = vec3_zero();
    t->rotation = vec3_zero();
    t->scale = vec3_one();

    return t;
}
// destroys the given transform object
void transform_destroy(Transform* t) {
    free(t);
}

// // SETTERS
// // sets the given transform position
// void transform_setPosAll(Transform* t, float x, float y, float z) {
//     t->position.x = x;
//     t->position.y = y;
//     t->position.z = z;
// }
// // sets the given transform position
// void transform_setPos(Transform* t, vec3 pos) {
//     t->position = pos;
// }
// // sets the given transform x position
// void transform_setPosX(Transform* t, float x) {
//     t->position.x = x;
// }
// // sets the given transform y position
// void transform_setPosY(Transform* t, float y) {
//     t->position.y = y;
// }
// // sets the given transform z position
// void transform_setPosZ(Transform* t, float z) {
//     t->position.z = z;
// }

// // sets the given transform rotation
// void transform_setRotAll(Transform* t, float pitch, float yaw, float roll) {
//     t->rotation.x = pitch;
//     t->rotation.y = yaw;
//     t->rotation.z = roll;
// }
// // sets the given transform rotation
// void transform_setRot(Transform* t, vec3 rot) {
//     t->rotation = rot;
// }
// // sets the given transform x rotation
// void transform_setRotX(Transform* t, float pitch) {
//     t->rotation.x = pitch;
// }
// // sets the given transform y rotation
// void transform_setRotY(Transform* t, float yaw) {
//     t->rotation.y = yaw;
// }
// // sets the given transform z rotation
// void transform_setRotZ(Transform* t, float roll) {
//     t->rotation.z = roll;
// }

// // sets the given transform scale
// void transform_setScaleAll(Transform* t, float xs, float ys, float zs) {
//     t->scale.x = xs;
//     t->scale.y = ys;
//     t->scale.z = zs;
// }
// // sets the given transform scale
// void transform_setScale(Transform* t, vec3 scale) {
//     t->scale = scale;
// }
// // sets the given transform x scale
// void transform_setScaleX(Transform* t, float xs) {
//     t->scale.x = xs;
// }
// // sets the given transform y scale
// void transform_setScaleY(Transform* t, float ys) {
//     t->scale.y = ys;
// }
// // sets the given transform z scale
// void transform_setScaleZ(Transform* t, float zs) {
//     t->scale.z = zs;
// }

// OPERATIONS
// increments the given transform position by the given translation vector (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
void transform_changePosition(Transform* t, vec3 translation) {
    t->position = vec3_sum(t->position, translation);
}

// increments the given transform rotation by the given rotation vector (pitch, yaw, roll) (angles are in degrees)
void transform_changeRotation(Transform* t, vec3 rotation) {
    t->rotation = vec3_sum(t->rotation, rotation);
}

// increment the the given transform scale by the given scaling vector (xs, ys, zs)
void transform_changeScale(Transform* t, vec3 scaling) {
    t->scale = vec3_sum(t->scale, scaling);
}

// MATRIX
// calculates the model matrix for the given transform and returns it
mat4 transform_getModelMatrix(Transform* t) {
    mat4 scaleMatrix = mat4_scaling(t->scale);
    mat4 rotationMatrix = mat4_eulerRotation(t->rotation);
    mat4 translationMatrix = mat4_translation(t->position);

    // scale first, then rotate and finally translate
    mat4 model = mat4_multiply(translationMatrix, rotationMatrix);
    model = mat4_multiply(model, scaleMatrix);

    return model;
}