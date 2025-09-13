/*
LINEAR ALGEBRA MODULE
Contains float vector 2, 3, 4 definitions,
float matrix 2, 3, 4 definitions
and stack allocating vector and matrix constructors.
For dynamically allocating vector and matrix constructors
there will be the transform module, which will be part of the game_object module
(extended object lifetime makes heap allocation a better approach).
*/

#include <string.h>
#include <math.h>

#include "engine/utils/console.h"

#include "engine/math/linal.h"

#define PI 3.14159265359
#define DEGREES_TO_RADIANS PI / 180
#define RADIANS_TO_DEGREES 180 / PI

// STACK ALLOCATING CONSTRUCTORS

// VECTORS
// vec2 stack allocating constructor
vec2 vec2_new(float x, float y) {
    return (vec2) {
        .x = x,
        .y = y
    };
}
// vec3 stack allocating constructor
vec3 vec3_new(float x, float y, float z) {
    return (vec3) {
        .x = x,
        .y = y,
        .z = z
    };
}
// vec4 stack allocating constructor
vec4 vec4_new(float x, float y, float z, float w) {
    return (vec4) {
        .x = x,
        .y = y,
        .z = z,
        .w = w
    };
}

// SPECIAL VECTORS

// returns a float vector 2 with all components set to 0
vec2 vec2_zero() {
    return (vec2) {0};
}
// returns a float vector 2 with all components set to 1
vec2 vec2_one() {
    return (vec2) {1};
}
// returns a float vector 3 with all components set to 0
vec3 vec3_zero() {
    return (vec3) {0};
}
// returns a float vector 3 with all components set to 1
vec3 vec3_one() {
    return (vec3) {1};
}
// returns a float vector 4 with all components set to 0
vec4 vec4_zero() {
    return (vec4) {0};
}
// returns a float vector 4 with all components set to 1
vec4 vec4_one() {
    return (vec4) {1};
}

// MATRICES
// mat2 stack allocating constructor
mat2 mat2_new(float entries[4]) {
    mat2 m;
    memcpy(m.entries, entries, sizeof(m.entries));
    return m;
}
// mat3 stack allocating constructor
mat3 mat3_new(float entries[9]) {
    mat3 m;
    memcpy(m.entries, entries, sizeof(m.entries));
    return m;
}
// mat4 stack allocating constructor
mat4 mat4_new(float entries[16]) {
    mat4 m;
    memcpy(m.entries, entries, sizeof(m.entries));
    return m;
}

// GETTERS
// gets the given matrix entry at the given row and column and returns the value
float mat2_get(mat2* m, unsigned char row, unsigned char column) {
    return m->entries[column + row * 2];
}
// gets the given matrix entry at the given row and column and returns the value
float mat3_get(mat3* m, unsigned char row, unsigned char column) {
    return m->entries[column + row * 3];
}
// gets the given matrix entry at the given row and column and returns the value
float mat4_get(mat4* m, unsigned char row, unsigned char column) {
    return m->entries[column + row * 4];
}

// SETTERS
// sets the given matrix entry at the given row and column to the specified entry value
void mat2_set(mat2* m, unsigned char row, unsigned char column, float value) {
    if (row >= 2 || column >= 2) {
        console_warning("Invalid row and/or column for (%u, %u) in a 2x2 matrix", row, column);
        return;
    }
    m->entries[column + row * 2] = value;
}
// sets the given matrix entry at the given row and column to the specified entry value
void mat3_set(mat3* m, unsigned char row, unsigned char column, float value) {
    if (row >= 3 || column >= 3) {
        console_warning("Invalid row and/or column for (%u, %u) in a 3x3 matrix", row, column);
        return;
    }
    m->entries[column + row * 3] = value;
}
// sets the given matrix entry at the given row and column to the specified entry value
void mat4_set(mat4* m, unsigned char row, unsigned char column, float value) {
    if (row >= 4 || column >= 4) {
        console_warning("Invalid row and/or column for (%u, %u) in a 4x4 matrix", row, column);
        return;
    }
    m->entries[column + row * 4] = value;
}

// sets the given matrix entries all at once to the given entries array
void mat2_setAll(mat2* m, float entries[4]) {
    memcpy(m->entries, entries, sizeof(m->entries));
}
// sets the given matrix entries all at once to the given entries array
void mat3_setAll(mat3* m, float entries[9]) {
    memcpy(m->entries, entries, sizeof(m->entries));
}
// sets the given matrix entries all at once to the given entries array
void mat4_setAll(mat4* m, float entries[16]) {
    memcpy(m->entries, entries, sizeof(m->entries));
}

// SPECIAL MATRICES
// returns a 2x2 float matrix with all entries set to 0
mat2 mat2_zero() {
    return (mat2) {0};
}
// returns a 2x2 float identity matrix
mat2 mat2_identity() {
    float entries[4] = {
        1, 0,
        0, 1
    };
    return mat2_new(entries);
}
// returns a 2x2 float translation matrix based on the given translation vector
// mat2 mat2_translation(vec2 translation);
// returns a 2x2 float rotation matrix based on the given angle value
mat2 mat2_rotation(float angle) {
    const float theta = angle * DEGREES_TO_RADIANS;
    float entries[4] = {
        cos(theta), -sin(theta),
        sin(theta), cos(theta)
    };
    return mat2_new(entries);
}
// returns a 2x2 float scaling matrix based on the given scale value
mat2 mat2_scaling(vec2 scaling) {
    mat2 m = mat2_zero();
    mat2_set(&m, 0, 0, scaling.x);
    mat2_set(&m, 1, 1, scaling.y);
    return m;
}

// returns a 3x3 float matrix with all entries set to 0
mat3 mat3_zero() {
    return (mat3) {0};
}
// returns a 3x3 float identity matrix
mat3 mat3_identity() {
    float entries[9] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    return mat3_new(entries);
}
// returns a 3x3 float translation matrix based on the given translation vector
// mat3 mat3_translation(vec3 translation);
// returns a 3x3 float rotation matrix based on the given angle value
// axes can either be AXIS_X, AXIS_Y, AXIS_Z or a combination of these given by doing bitwise OR
mat3 mat3_rotation(unsigned char axes, float angle) {
    const float theta = angle * DEGREES_TO_RADIANS;
    mat3 result = mat3_identity();

    float rx_entries[9] = {
        1, 0, 0,
        0, cos(theta), -sin(theta),
        0, sin(theta), cos(theta)
    };

    float ry_entries[9] = {
        cos(theta), 0, -sin(theta),
        0, 1, 0,
        sin(theta), 0, cos(theta)
    };

    float rz_entries[9] = {
        cos(theta), -sin(theta), 0,
        sin(theta), cos(theta), 0,
        0, 0, 1
    };

    if (axes & AXIS_X) {
        mat3 rx = mat3_new(rx_entries);
        result = mat3_multiply(rx, result);
    }

    if (axes & AXIS_Y) {
        mat3 ry = mat3_new(ry_entries);
        result = mat3_multiply(ry, result);
    }

    if (axes & AXIS_Z) {
        mat3 rz = mat3_new(rz_entries);
        result = mat3_multiply(rz, result);
    }

    if (axes == 0b000) {
        console_warning("Invalid axes flag for %u", axes);
    }

    return result;
}
// returns a 3x3 float scaling matrix based on the given scale value
mat3 mat3_scaling(vec3 scaling) {
    float entries[9] = {
        scaling.x, 0, 0,
        0, scaling.y, 0,
        0, 0, scaling.z
    };
    return mat3_new(entries);
}

// returns a 4x4 float matrix with all entries set to 0
mat4 mat4_zero() {
    return (mat4) {0};
}
// returns a 4x4 float identity matrix
mat4 mat4_identity() {
    float entries[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    return mat4_new(entries);
}
// returns a 4x4 float translation matrix based on the given translation vector
mat4 mat4_translation(vec3 translation) {
    mat4 t = mat4_identity();
    mat4_set(&t, 0, 3, translation.x);
    mat4_set(&t, 1, 3, translation.y);
    mat4_set(&t, 2, 3, translation.z);
    return t;
}
// returns a 4x4 float rotation matrix based on the given rotation vector
// axis is a unit vector representing the direction of the rotation axis.
// by default the rotation axis runs through the origin (0, 0, 0),
// meaning that in order to rotate around a different pivot you must first
// translate the object so that the pivot is located at the origin
// (so translate it by the negated pivot position vector)
mat4 mat4_rotation(vec3 axis, float angle) {
    // don't worry about pointer problems because even thoug axis is not the original but a copy,
    // the normalized version of it will be used only inside of this function here
    if (vec3_magnitude(axis) != 1) {
        axis = vec3_normalize(axis);
    }

    const float theta = angle * DEGREES_TO_RADIANS;
    const float cosT = cos(theta);
    const float sinT = sin(theta);
    const float Rx = axis.x;
    const float Ry = axis.y;
    const float Rz = axis.z;
    float entries[16] = {
        cosT + (Rx*Rx * (1 - cosT)),            (Rx * Ry * (1 - cosT)) - (Rz * sinT),   (Rx * Rz * (1 - cosT)) + (Ry * sinT),   0,
        (Ry * Rx * (1 - cosT)) + (Rz * sinT),   cosT + (Ry*Ry * (1 - cosT)),            (Ry * Rz * (1 - cosT)) - (Rx * sinT),   0,
        (Rz * Rx * (1 - cosT)) - (Ry * sinT),   (Rz * Ry * (1 - cosT)) + (Rx * sinT),   cosT + (Rz*Rz * (1 - cosT)),            0,
        0,                                      0,                                      0,                                      1
    };

    return mat4_new(entries);
}
// returns a 4x4 float rotation matrix based on the given rotation vector as Tait-Bryan angles (pitch, yaw, roll)
mat4 mat4_eulerRotation(vec3 angles) {
    mat4 xRot = mat4_rotation(vec3_new(1, 0, 0), angles.x);
    mat4 yRot = mat4_rotation(vec3_new(0, 1, 0), angles.y);
    mat4 zRot = mat4_rotation(vec3_new(0, 0, 1), angles.z);
    mat4 result;
    // combine the rotations backwards because the first multiplied is actually the last the gets applied
    result = mat4_multiply(zRot, yRot);
    result = mat4_multiply(result, xRot);
    return result;
}
// returns a 4x4 float scaling matrix based on the given scale value
mat4 mat4_scaling(vec3 scaling) {
    mat4 s = mat4_zero();
    mat4_set(&s, 0, 0, scaling.x);
    mat4_set(&s, 1, 1, scaling.y);
    mat4_set(&s, 2, 2, scaling.z);
    mat4_set(&s, 3, 3, 1);
    return s;
}

// returns an orthographic projection matrix given the projection parameters
mat4 matrix_orthographic_projection(float left, float right, float bottom, float top, float near, float far) {
    float entries[16] = {
        2 / (right - left), 0,                  0,                  -(right + left) / (right - left),
        0,                  2 / (top - bottom), 0,                  -(top + bottom) / (top - bottom),
        0,                  0,                  -2 / (far - near),  -(far + near) / (far - near),
        0,                  0,                  0,                  1
    };
    mat4 proj = mat4_new(entries);
}
// returns a perspective projection matrix given the projection parameters
// FOV should be provided in DEGREES
mat4 matrix_perspective_projection(int width, int height, float fov, float near, float far) {
    const float aspectRatio = (float) height / (float) width;
    const float tanHalfFov = tan(fov * DEGREES_TO_RADIANS / 2);
    
    float entries[16] = {
        1 / (aspectRatio * tanHalfFov), 0,              0,                              0,
        0,                              1 / tanHalfFov, 0,                              0,
        0,                              0,              -(far + near) / (far - near),   - (2 * far * near) / (far - near),
        0,                              0,              -1,                             0
    };
    mat4 proj = mat4_new(entries);
}

// QUATERNIONS
// quat stack allocating constructor
quat quat_new(float w, float x, float y, float z) {
    return (quat) {
        .w = w,
        .x = x,
        .y = y,
        .z = z
    };
}

// returns a quaternion with all components set to 0
quat quat_zero() {
    return (quat) {0};
}
// returns an identity quaternion
quat quat_identity() {
    return (quat) {
        .w = 1,
        .x = 0,
        .y = 0,
        .z = 0
    };
}
// returns a rotation quaternion based on the given axis direction and angle value
quat quat_rotation(vec3 axis, float angle) {
    const float theta = angle * DEGREES_TO_RADIANS;
    const float cosHalfT = cos(theta / 2);
    const float sinHalfT = sin(theta / 2);
    return quat_new(
        cosHalfT,
        axis.x * sinHalfT,
        axis.y * sinHalfT,
        axis.z * sinHalfT
    );
}

// LINEAR ALGEBRA OPERATIONS

// VECTORS
// sum, diff, scale, dot, cross, inverse, magnitude, normalise (versor)

// VECTOR SUM
// sums two vectors and returns the result
vec2 vec2_sum(vec2 v0, vec2 v1) {
    return vec2_new(
        v0.x + v1.x,
        v0.y + v1.y
    );
}
// sums two vectors and returns the result
vec3 vec3_sum(vec3 v0, vec3 v1) {
    return vec3_new(
        v0.x + v1.x,
        v0.y + v1.y,
        v0.z + v1.z
    );
}
// sums two vectors and returns the result
vec4 vec4_sum(vec4 v0, vec4 v1) {
    return vec4_new(
        v0.x + v1.x,
        v0.y + v1.y,
        v0.z + v1.z,
        v0.w + v1.w
    );
}

// VECTOR DIFFERENCE
// subtracts two vectors and returns the result
vec2 vec2_difference(vec2 v0, vec2 v1) {
    return vec2_new(
        v0.x - v1.x,
        v0.y - v1.y
    );
}
// subtracts two vectors and returns the result
vec3 vec3_difference(vec3 v0, vec3 v1) {
    return vec3_new(
        v0.x - v1.x,
        v0.y - v1.y,
        v0.z - v1.z
    );
}
// subtracts two vectors and returns the result
vec4 vec4_difference(vec4 v0, vec4 v1) {
    return vec4_new(
        v0.x - v1.x,
        v0.y - v1.y,
        v0.z - v1.z,
        v0.w - v1.w
    );
}

// VECTOR SCALE
// scales a vector by the s float parameter and returns the result
vec2 vec2_scale(vec2 v, float s) {
    return vec2_new(
        s * v.x,
        s * v.y
    );
}
// scales a vector by the s float parameter and returns the result
vec3 vec3_scale(vec3 v, float s) {
    return vec3_new(
        s * v.x,
        s * v.y,
        s * v.z
    );
}
// scales a vector by the s float parameter and returns the result
vec4 vec4_scale(vec4 v, float s) {
    return vec4_new(
        s * v.x,
        s * v.y,
        s * v.z,
        s * v.w
    );
}

// VECTOR DOT PRODUCT
// evaluates the dot product between v0 and v1 and returns the result
float vec2_dot(vec2 v0, vec2 v1) {
    return (v0.x * v1.x) + (v0.y * v1.y);
}
// evaluates the dot product between v0 and v1 and returns the result
float vec3_dot(vec3 v0, vec3 v1) {
    return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
}
// evaluates the dot product between v0 and v1 and returns the result
float vec4_dot(vec4 v0, vec4 v1) {
    return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z) + (v0.w * v1.w);
}

// VECTOR CROSS PRODUCT
// evaluates the cross product between v0 and v1 and returns the result
vec3 vec3_cross(vec3 v0, vec3 v1) {
    return vec3_new(
        (v0.y * v1.z) - (v1.y * v0.z),
        (v1.x * v0.z) - (v0.x * v1.z),
        (v0.x * v1.y) - (v1.x * v0.y)
    );
}

// VECTOR INVERSE
// swaps the specified component(s) sign of the given vector and returns the result
// target can either be TARGET_X, TARGET_Y or a combination of these given by doing bitwise OR
vec2 vec2_negate(vec2 v, unsigned char target) {
    return vec2_new(
        v.x * (target & TARGET_X ? -1 : 1),
        v.y * (target & TARGET_Y ? -1 : 1)
    );
}
// swaps the specified component(s) sign of the given vector and returns the result
// target can either be TARGET_X, TARGET_Y or TARGET_Z or a combination of these given by doing bitwise OR
vec3 vec3_negate(vec3 v, unsigned char target) {
    return vec3_new(
        v.x * (target & TARGET_X ? -1 : 1),
        v.y * (target & TARGET_Y ? -1 : 1),
        v.z * (target & TARGET_Z ? -1 : 1)
    );
}
// swaps the specified component(s) sign of the given vector and returns the result
// target can either be TARGET_X, TARGET_Y, TARGET_Z or TARGET_W or a combination of these given by doing bitwise OR
vec4 vec4_negate(vec4 v, unsigned char target) {
    return vec4_new(
        v.x * (target & TARGET_X ? -1 : 1),
        v.y * (target & TARGET_Y ? -1 : 1),
        v.z * (target & TARGET_Z ? -1 : 1),
        v.w * (target & TARGET_W ? -1 : 1)
    );
}

// VECTOR MAGNITUDE
// evaluates the given vector magnitude and returns it
float vec2_magnitude(vec2 v) {
    return sqrt(vec2_dot(v, v));
}
// evaluates the given vector magnitude and returns it
float vec3_magnitude(vec3 v) {
    return sqrt(vec3_dot(v, v));
}
// evaluates the given vector magnitude and returns it
float vec4_magnitude(vec4 v) {
    return sqrt(vec4_dot(v, v));
}

// VECTOR NORMALIZE
// normalizes the given vector and returns the result
vec2 vec2_normalize(vec2 v) {
    return vec2_scale(v, 1 / vec2_magnitude(v));
}
// normalizes the given vector and returns the result
vec3 vec3_normalize(vec3 v) {
    return vec3_scale(v, 1 / vec3_magnitude(v));
}
// normalizes the given vector and returns the result
vec4 vec4_normalize(vec4 v) {
    return vec4_scale(v, 1 / vec4_magnitude(v));
}

// MATRICES
// sum, diff, scale, mul, (adj, det, rank), transpose, negate (scale by -1)

// MATRIX SUM
// sums two matrices and returns the result
mat2 mat2_sum(mat2 m0, mat2 m1) {
    mat2 result;
    for (int i = 0; i < 4; i++) {
        result.entries[i] = m0.entries[i] + m1.entries[i];
    }
    return result;
}
// sums two matrices and returns the result
mat3 mat3_sum(mat3 m0, mat3 m1) {
    mat3 result;
    for (int i = 0; i < 9; i++) {
        result.entries[i] = m0.entries[i] + m1.entries[i];
    }
    return result;
}
// sums two matrices and returns the result
mat4 mat4_sum(mat4 m0, mat4 m1) {
    mat4 result;
    for (int i = 0; i < 16; i++) {
        result.entries[i] = m0.entries[i] + m1.entries[i];
    }
    return result;
}

// MATRIX DIFFERENCE
// subtracts two matrices and returns the result
mat2 mat2_difference(mat2 m0, mat2 m1) {
    mat2 result;
    for (int i = 0; i < 4; i++) {
        result.entries[i] = m0.entries[i] - m1.entries[i];
    }
    return result;
}
// subtracts two matrices and returns the result
mat3 mat3_difference(mat3 m0, mat3 m1) {
    mat3 result;
    for (int i = 0; i < 9; i++) {
        result.entries[i] = m0.entries[i] - m1.entries[i];
    }
    return result;
}
// subtracts two matrices and returns the result
mat4 mat4_difference(mat4 m0, mat4 m1) {
    mat4 result;
    for (int i = 0; i < 16; i++) {
        result.entries[i] = m0.entries[i] - m1.entries[i];
    }
    return result;
}

// MATRIX SCALE
// scales a matrix by the given s float parameter and returns the result
mat2 mat2_scale(mat2 m, float s) {
    mat2 result;
    for (int i = 0; i < 4; i++) {
        result.entries[i] = s * m.entries[i];
    }
    return result;
}
// scales a matrix by the given s float parameter and returns the result
mat3 mat3_scale(mat3 m, float s) {
    mat3 result;
    for (int i = 0; i < 9; i++) {
        result.entries[i] = s * m.entries[i];
    }
    return result;
}
// scales a matrix by the given s float parameter and returns the result
mat4 mat4_scale(mat4 m, float s) {
    mat4 result;
    for (int i = 0; i < 16; i++) {
        result.entries[i] = s * m.entries[i];
    }
    return result;
}

// MATRIX MULTIPLICATION
// does exactly what the name says
// r0 and c1 are respectively the number of rows and columns of the first and second matrix
// n is the number of columns of the first matrix as well as the number of rows of the second matrix
// (they should be the same to be able to multiply the two matrices together)
// the result of the multiplication is stored in the array pointed by result
void generic_matrix_multiplication(float* m0, float* m1, unsigned int r0, unsigned int c1, unsigned int n, float* result) {
    for (int i = 0; i < r0; i++) {
        for (int j = 0; j < c1; j++) {
            float currentEntry = 0;
            for (int k = 0; k < n; k++) {
                currentEntry += m0[k + i * n] * m1[j + k * c1];
            }
            result[i + j * n] = currentEntry;
        }
    }
}

// multiplies two matrices and returns the result
mat2 mat2_multiply(mat2 m0, mat2 m1) {
    mat2 result;
    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         float currentEntry = 0;
    //         for (int k = 0; k < 2; k++) {
    //             currentEntry += m0.entries[k + i * 2] * m1.entries[j + k * 2];
    //         }
    //         result.entries[i + j * 2] = currentEntry;
    //     }
    // }
    generic_matrix_multiplication(m0.entries, m1.entries, 2, 2, 2, &result);
    return result;
}
// multiplies two matrices and returns the result
mat3 mat3_multiply(mat3 m0, mat3 m1) {
    mat3 result;
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         float currentEntry = 0;
    //         for (int k = 0; k < 3; k++) {
    //             currentEntry += m0.entries[k + i * 3] * m1.entries[j + k * 2];
    //         }
    //         result.entries[i + j * 3] = currentEntry;
    //     }
    // }
    generic_matrix_multiplication(m0.entries, m1.entries, 3, 3, 3, &result);
    return result;
}
// multiplies two matrices and returns the result
mat4 mat4_multiply(mat4 m0, mat4 m1) {
    mat4 result;
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         float currentEntry = 0;
    //         for (int k = 0; k < 4; k++) {
    //             currentEntry += m0.entries[k + i * 4] * m1.entries[j + k * 4];
    //         }
    //         result.entries[i + j * 4] = currentEntry;
    //     }
    // }
    generic_matrix_multiplication(m0.entries, m1.entries, 4, 4, 4, &result);
    return result;
}

// MATRIX TRANSPOSE
// transposes a matrix and returns the result
mat2 mat2_transpose(mat2 m) {
    // manually transposing this one
    const float tmp = m.entries[1];
    m.entries[1] = m.entries[2];
    m.entries[2] = tmp;
    return m;
}

// transposes an entries array given the matrix size
// it modifies the original array
void generic_matrix_transpose(float* entries, unsigned int size) {
    // here it's traversing the matrix from the top right corner to the bottom left corner
    // as transposing a matrix will leave the main diagonal untouched,
    // it's sufficient to run the loop for the two triangles devided by said diagonal
    // and swap the elements simmetrical relatively to the same diagonal

    // row loop
    for (int i = 0; i < size - 1; i++) {
        // column loop
        for (int j = i + 1; j < size; j++) {
            const int currentIndex = j + i * size;
            // evaluate the simmetrical element coordinates (just by swapping the row with the column)
            const int simmetricalIndex = i + j * size;
            // do the swap
            float tmp = entries[currentIndex];
            entries[currentIndex] = entries[simmetricalIndex];
            entries[simmetricalIndex] = tmp;
        }
    }
}

// transposes a matrix and returns the result
mat3 mat3_transpose(mat3 m) {
    // this modifies the actual m.entries array
    // however, rememeber that m.entries is a copy, so the original remains untouched
    // that's why it's returned
    generic_matrix_transpose(m.entries, 3);

    return m;
}
// transposes a matrix and returns the result
mat4 mat4_transpose(mat4 m) {
    // this modifies the actual m.entries array
    // however, rememeber that m.entries is a copy, so the original remains untouched
    // that's why it's returned
    generic_matrix_transpose(m.entries, 4);

    return m;
}

// MATRIX NEGATE
// negates a matrix (scales it by -1) and returns the result
mat2 mat2_negate(mat2 m) {
    return mat2_scale(m, -1);
}
// negates a matrix (scales it by -1) and returns the result
mat3 mat3_negate(mat3 m) {
    return mat3_scale(m, -1);
}
// negates a matrix (scales it by -1) and returns the result
mat4 mat4_negate(mat4 m) {
    return mat4_scale(m, -1);
}

// QUATERNIONS
// multiply

// multiplies two quaternions and returns the result
quat quat_multiply(quat q0, quat q1) {
    quat result;
    result.x = q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y;
    result.y = q0.w * q1.y - q0.x * q1.z + q0.y * q1.w + q0.z * q1.x;
    result.z = q0.w * q1.z + q0.x * q1.y - q0.y * q1.x + q0.z * q1.w;
    result.w = q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
    return result;
}

// MIXED OPERATIONS
// 2D, 3D
// mul, (translate, rotate, scale)

// MATRIX with VECTOR MULTIPLICATION
// multiplies a matrix by a vector and returns the result
vec2 mat2_vec2_multiply(mat2 m, vec2 v) {
    float vectorMatrix[2] = { v.x, v.y };
    float result[2];
    generic_matrix_multiplication(m.entries, vectorMatrix, 2, 1, 2, result);
    return vec2_new(result[0], result[1]);
}
// multiplies a matrix by a vector and returns the result
vec3 mat3_vec3_multiply(mat3 m, vec3 v) {
    float vectorMatrix[3] = { v.x, v.y, v.z };
    float result[3];
    generic_matrix_multiplication(m.entries, vectorMatrix, 3, 1, 3, result);
    return vec3_new(result[0], result[1], result[2]);
}
// multiplies a matrix by a vector and returns the result
vec4 mat4_vec4_multiply(mat4 m, vec4 v) {
    float vectorMatrix[4] = { v.x, v.y, v.z, v.w };
    float result[4];
    generic_matrix_multiplication(m.entries, vectorMatrix, 4, 1, 4, result);
    return vec4_new(result[0], result[1], result[2], result[3]);
}

// MATRIX to QUATERNION and viceversa
// converts a rotation quaternion to a 4D rotation matrix
mat4 quat_to_mat4(quat q) {
    float x2 = q.x * q.x;
    float y2 = q.y * q.y;
    float z2 = q.z * q.z;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float yz = q.y * q.z;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    float wz = q.w * q.z;

    float entries[16] = {
        1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz),          2.0f * (xz + wy),          0.0f,
        2.0f * (xy + wz),        1.0f - 2.0f * (x2 + z2),   2.0f * (yz - wx),          0.0f,
        2.0f * (xz - wy),        2.0f * (yz + wx),          1.0f - 2.0f * (x2 + y2),   0.0f,
        0.0f,                    0.0f,                      0.0f,                      1.0f
    };

    return mat4_new(entries);
}
// converts a 4D rotation matrix to a rotation quaternion
quat mat4_to_quat(mat4 m) {
    quat result;

    // 1. calculate the trace of the 3x3 rotation part of the matrix
    const float m00 = m.entries[0];
    const float m11 = m.entries[1+1*4];
    const float m22 = m.entries[2+2*4];
    const float trace = m00 + m11 + m22;
    // 2. trace > 0
    if (trace > 0) {
        const float s = sqrt(trace + 1.0f) * 2.0f;
        
        result.w = 0.25f * s;
        result.x = (m.entries[1 + 2 * 4] - m.entries[2 + 1 * 4]) / s;
        result.y = (m.entries[2 + 0 * 4] - m.entries[0 + 2 * 4]) / s;
        result.z = (m.entries[0 + 1 * 4] - m.entries[1 + 0 * 4]) / s;
    // 3. trace <= 0
    } else if (trace <= 0) {
        // m00 is the greatest
        if (m00 > m11 && m00 > m22) {
            const float s = sqrt(1.0f + m.entries[0 + 0 * 4] - m.entries[1 + 1 * 4] - m.entries[2 + 2 * 4]) * 2.0f;
            
            result.w = (m.entries[1 + 2 * 4] - m.entries[2 + 1 * 4]) / s;
            result.x = 0.25f * s;
            result.y = (m.entries[1 + 0 * 4] + m.entries[0 + 1 * 4]) / s;
            result.z = (m.entries[2 + 0 * 4] + m.entries[0 + 2 * 4]) / s;
        // m11 is the greatest
        } else if (m11 > m00 && m11 > m22) {
            const float s = sqrt(1.0f + m.entries[1 + 1 * 4] - m.entries[0 + 0 * 4] - m.entries[2 + 2 * 4]) * 2.0f;
            
            result.w = (m.entries[2 + 0 * 4] - m.entries[0 + 2 * 4]) / s;
            result.x = (m.entries[1 + 0 * 4] + m.entries[0 + 1 * 4]) / s;
            result.y = 0.25f * s;
            result.z = (m.entries[2 + 1 * 4] + m.entries[1 + 2 * 4]) / s;
        // m22 is the greatest
        } else if (m22 > m00 && m22 > m11) {
            const float s = sqrt(1.0f + m.entries[2 + 2 * 4] - m.entries[0 + 0 * 4] - m.entries[1 + 1 * 4]) * 2.0f;
            
            result.w = (m.entries[0 + 1 * 4] - m.entries[1 + 0 * 4]) / s;
            result.x = (m.entries[2 + 0 * 4] + m.entries[0 + 2 * 4]) / s;
            result.y = (m.entries[2 + 1 * 4] + m.entries[1 + 2 * 4]) / s;
            result.z = 0.25f * s;
        }
    }
}

// OUTPUT
// prints out the given vector (precision specifies the number of decimal digits)
void print_vec2(vec2 v, unsigned int precision) {
    console_output("(%.*f, %.*f)", precision, v.x, precision, v.y);
}
// prints out the given vector (precision specifies the number of decimal digits)
void print_vec3(vec3 v, unsigned int precision) {
    console_output("(%.*f, %.*f, %.*f)", precision, v.x, precision, v.y, precision, v.z);
}
// prints out the given vector (precision specifies the number of decimal digits)
void print_vec4(vec4 v, unsigned int precision) {
    console_output("(%.*f, %.*f, %.*f, %.*f)", precision, v.x, precision, v.y, precision, v.z, precision, v.w);
}

void generic_matrix_printer(float* entries, unsigned int size, unsigned int precision) {
    // row loop
    for (int i = 0; i < size; i++) {
        // print the first entry in the row
        console_printf("[%.*f", precision, entries[i]);
        // column loop
        for (int j = 1; j < size; j++) {
            console_printf(", %.*f", precision, entries[i + j * size]);
        }
        // print the closing square bracket at the end of each line
        console_printf("]\n");
    }
}
// prints out the given matrix (precision specifies the number of decimal digits)
void print_mat2(mat2 m, unsigned int precision) {
    generic_matrix_printer(m.entries, 2, precision);
}
// prints out the given matrix (precision specifies the number of decimal digits)
void print_mat3(mat3 m, unsigned int precision) {
    generic_matrix_printer(m.entries, 3, precision);
}
// prints out the given matrix (precision specifies the number of decimal digits)
void print_mat4(mat4 m, unsigned int precision) {
    generic_matrix_printer(m.entries, 4, precision);
}

// prints out the given quaternion (precision specifies the number of decimal digits)
void print_quat(quat q, unsigned int precision) {
    console_output("[%.*f, (%.*f, %.*f, %.*f)]", precision, q.w, precision, q.x, precision, q.y, precision, q.z);
}