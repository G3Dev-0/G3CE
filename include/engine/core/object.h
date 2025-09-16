/*
OBJECT:
An object is a structure made of a Mesh and a Transform.
It's basically an easier way to manage objects in code.
*/

#ifndef OBJECT_H
#define OBJECT_H

/*
we want to be able to:
- create object
- destroy object

- set position by vector
- set position by values
same for rotation and scale

- changePosition, rotation and scale (increment functions)

- assign a shader
*/

#include "engine/gfx/mesh.h"
#include "engine/math/linal.h"
#include "engine/math/transform.h"

typedef struct {
    Mesh mesh;
    Transform transform;
    unsigned int shader; // if set to 0 it will be using the currently active shader (you can't disable shaders when rendering so 0 is not a valid ID (it's used by OpenGL to disable shaders))
} Object;

// creates a stack allocated object using the given mesh, with a blank transform an assigned shader = 0. It does not need to be destroyed
Object object_new(Mesh mesh);

// creates an object with a given mesh and a blank transform (by default the assigned shader is 0)
// YOU MUST DESTROY IT ONCE YOU'RE DONE WITH IT TO AVOID MEMORY LEAKS
Object* object_create(Mesh mesh);
// destroys the given object
void object_destroy(Object* o);

// SETTERS
// sets the given object transform to the given transform
void object_setTransformByTransform(Object* o, Transform t);
// sets the given object transform vectors to the given transform vectors
void object_setTransformByVectors(Object* o, vec3 position, vec3 rotation, vec3 scale);
// sets the given object transform values to the given transform values
void object_setTransformByValues(Object* o, float x, float y, float z, float pitch, float yaw, float roll, float xs, float ys, float zs);

// sets the given object position to the given position vector
void object_setPositionByVector(Object* o, vec3 position);
// sets the given object rotation to the given rotation vector
void object_setRotationByVector(Object* o, vec3 rotation);
// sets the given object scale to the given scale vector
void object_setScaleByVector(Object* o, vec3 scale);

// sets the given object position to the given position values
void object_setPositionByValues(Object* o, float x, float y, float z);
// sets the given object rotation to the given rotation values
void object_setRotationByValues(Object* o, float pitch, float yaw, float roll);
// sets the given object scale to the given scale values
void object_setScaleByValues(Object* o, float xs, float ys, float zs);

// OPERATIONS
// increments the given object position by the given translation vector
void object_changePositionByVector(Object* o, vec3 translation);
// increments the given object rotation by the given rotation vector
void object_changeRotationByVector(Object* o, vec3 rotation);
// increments the given object scale by the given scaling vector
void object_changeScaleByVector(Object* o, vec3 scaling);

// increments the given object position by the given position values
void object_changePositionByValues(Object* o, float xm, float ym, float zm);
// increments the given object rotation by the given rotation values
void object_changeRotationByValues(Object* o, float xr, float yr, float zr);
// increments the given object scale by the given scale values
void object_changeScaleByValues(Object* o, float xs, float ys, float zs);

// assigns the given shader to the given object
// when calling renderer_renderObject(Object* o) the assigned shader will be bound
// if the assigned shader is 0, the renderer will keep using the currently bound shader
void object_assignShader(Object* o, unsigned int shader);

#endif