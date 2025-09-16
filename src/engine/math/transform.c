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

// SETTERS
// sets the given transform position to the given position values (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
void transform_setPosition(Transform* t, float x, float y, float z) {
    t->position.x = x;
    t->position.y = y;
    t->position.z = z;
}
// sets the given transform rotation to the given rotation values
void transform_setRotation(Transform* t, float pitch, float yaw, float roll) {
    t->rotation.x = pitch;
    t->rotation.y = yaw;
    t->rotation.z = roll;
}
// sets the given transform scale to the given scale values
void transform_setScale(Transform* t, float xs, float ys, float zs) {
    t->scale.x = xs;
    t->scale.y = ys;
    t->scale.z = zs;
}

// OPERATIONS
// increments the given transform position by the given translation vector (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
void transform_changePosition(Transform* t, vec3 translation) {
    t->position.x += translation.x;
    t->position.y += translation.y;
    t->position.z += translation.z;
}
// increments the given transform rotation by the given rotation vector (pitch, yaw, roll) (angles are in degrees)
void transform_changeRotation(Transform* t, vec3 rotation) {
    t->rotation.x += rotation.x;
    t->rotation.y += rotation.y;
    t->rotation.z += rotation.z;
}
// increment the the given transform scale by the given scaling vector (xs, ys, zs)
void transform_changeScale(Transform* t, vec3 scaling) {
    t->scale.x += scaling.x;
    t->scale.y += scaling.y;
    t->scale.z += scaling.z;
}

// increments the given transform position by the given translation values (x, y, z) (right-handed system: +x to the right, +y up, +z towards you that are reading this right now!)
void transform_changePositionValues(Transform* t, float xm, float ym, float zm) {
    t->position.x += xm;
    t->position.y += ym;
    t->position.z += zm;
}
// increments the given transform rotation by the given rotation values (pitch, yaw, roll) (angles are in degrees)
void transform_changeRotationValues(Transform* t, float xr, float yr, float zr) {
    t->rotation.x += xr;
    t->rotation.y += yr;
    t->rotation.z += zr;
}
// increment the the given transform scale by the given scaling values (xs, ys, zs)
void transform_changeScaleValues(Transform* t, float xs, float ys, float zs) {
    t->scale.x += xs;
    t->scale.y += ys;
    t->scale.z += zs;
}

// MATRIX
// calculates the model matrix for the given transform and returns it
mat4 transform_getModelMatrix(Transform* t) {
    mat4 scaleMatrix = mat4_scaling(t->scale);

    // TEST
    // use a quaternion based rotation system
    quat xRot = quat_rotation(vec3_new(1, 0, 0), t->rotation.x);
    quat yRot = quat_rotation(vec3_new(0, 1, 0), t->rotation.y);
    quat zRot = quat_rotation(vec3_new(0, 0, 1), t->rotation.z);
    quat rotationQuat = quat_multiply(xRot, yRot);
    rotationQuat = quat_multiply(rotationQuat, zRot);
    // convert to rotation matrix
    mat4 rotationMatrix = quat_to_mat4(rotationQuat);
    
    // IF TEST FAILES USE THIS
    // mat4 rotationMatrix = mat4_eulerRotation(t->rotation);
    
    mat4 translationMatrix = mat4_translation(t->position);

    // scale first, then rotate and finally translate
    mat4 model = mat4_multiply(translationMatrix, rotationMatrix);
    model = mat4_multiply(model, scaleMatrix);

    return model;
}