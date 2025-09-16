/*
OBJECT:
An object is a structure made of a Mesh and a Transform.
It's basically an easier way to manage objects in code.
*/

#include <stdlib.h>

#include "engine/utils/console.h"

#include "engine/core/object.h"

// creates a stack allocated object using the given mesh, with a blank transform an assigned shader = 0. It does not need to be destroyed
Object object_new(Mesh mesh) {
    return (Object) {
        .mesh = mesh,
        .transform = transform_new(),
        .shader = 0
    };
}

// creates an object with a given mesh and a blank transform (by default the assigned shader is 0)
// YOU MUST DESTROY IT ONCE YOU'RE DONE WITH IT TO AVOID MEMORY LEAKS
Object* object_create(Mesh mesh) {
    Object* o = (Object*) malloc(sizeof(Object));
    if (o == NULL) {
        console_error("Failed to allocate memory for the object");
        return NULL;
    }

    o->mesh = mesh;
    o->transform = transform_new();
    o->shader = 0;
    
    return o;
}
// destroys the given object
void object_destroy(Object* o) {
    free(o);
}

// SETTERS
// sets the given object transform to the given transform
void object_setTransformByTransform(Object* o, Transform t) {
    o->transform = t;
}
// sets the given object transform vectors to the given transform vectors
void object_setTransformByVectors(Object* o, vec3 position, vec3 rotation, vec3 scale) {
    o->transform.position = position;
    o->transform.rotation = rotation;
    o->transform.scale = scale;
}
// sets the given object transform values to the given transform values
void object_setTransformByValues(Object* o, float x, float y, float z, float pitch, float yaw, float roll, float xs, float ys, float zs) {
    o->transform.position.x = x;
    o->transform.position.y = y;
    o->transform.position.z = z;
    o->transform.rotation.x = pitch;
    o->transform.rotation.y = yaw;
    o->transform.rotation.z = roll;
    o->transform.scale.x = xs;
    o->transform.scale.y = ys;
    o->transform.scale.z = zs;
}

// sets the given object position to the given position vector
void object_setPositionByVector(Object* o, vec3 position) {
    o->transform.position = position;
}
// sets the given object rotation to the given rotation vector
void object_setRotationByVector(Object* o, vec3 rotation) {
    o->transform.rotation = rotation;
}
// sets the given object scale to the given scale vector
void object_setScaleByVector(Object* o, vec3 scale) {
    o->transform.scale = scale;
}

// sets the given object position to the given position values
void object_setPositionByValues(Object* o, float x, float y, float z) {
    o->transform.position.x = x;
    o->transform.position.y = y;
    o->transform.position.z = z;
}
// sets the given object rotation to the given rotation values
void object_setRotationByValues(Object* o, float pitch, float yaw, float roll) {
    o->transform.rotation.x = pitch;
    o->transform.rotation.y = yaw;
    o->transform.rotation.z = roll;
}
// sets the given object scale to the given scale values
void object_setScaleByValues(Object* o, float xs, float ys, float zs) {
    o->transform.scale.x = xs;
    o->transform.scale.y = ys;
    o->transform.scale.z = zs;
}

// OPERATIONS
// increments the given object position by the given translation vector
void object_changePositionByVector(Object* o, vec3 translation) {
    o->transform.position.x += translation.x;
    o->transform.position.y += translation.y;
    o->transform.position.z += translation.z;
}
// increments the given object rotation by the given rotation vector
void object_changeRotationByVector(Object* o, vec3 rotation) {
    o->transform.rotation.x += rotation.x;
    o->transform.rotation.y += rotation.y;
    o->transform.rotation.z += rotation.z;
}
// increments the given object scale by the given scaling vector
void object_changeScaleByVector(Object* o, vec3 scaling) {
    o->transform.scale.x += scaling.x;
    o->transform.scale.y += scaling.y;
    o->transform.scale.z += scaling.z;
}

// increments the given object position by the given position values
void object_changePositionByValues(Object* o, float xm, float ym, float zm) {
    o->transform.position.x += xm;
    o->transform.position.y += ym;
    o->transform.position.z += zm;
}
// increments the given object rotation by the given rotation values
void object_changeRotationByValues(Object* o, float xr, float yr, float zr) {
    o->transform.rotation.x += xr;
    o->transform.rotation.y += yr;
    o->transform.rotation.z += zr;
}
// increments the given object scale by the given scale values
void object_changeScaleByValues(Object* o, float xs, float ys, float zs) {
    o->transform.scale.x += xs;
    o->transform.scale.y += ys;
    o->transform.scale.z += zs;
}

// assigns the given shader to the given object
// when calling renderer_renderObject(Object* o) the assigned shader will be bound
// if the assigned shader is 0, the renderer will keep using the currently bound shader
void object_assignShader(Object* o, unsigned int shader) {
    o->shader = shader;
}