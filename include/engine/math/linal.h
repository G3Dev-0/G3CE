/*
LINEAR ALGEBRA MODULE
Contains float vector 2, 3, 4 definitions,
float matrix 2, 3, 4 definitions,
quaternion definitions
and stack allocating vector, matrix and quaternion constructors.
For dynamically allocating vector, matrix and quaternion constructors
there will be the transform module, which will be part of the game_object module
(extended object lifetime makes heap allocation a better approach).
*/

#ifndef LINAL_H
#define LINAL_H

#define PI 3.14159265359
#define DEGREES_TO_RADIANS PI / 180
#define RADIANS_TO_DEGREES 180 / PI

// float Vector 2
typedef struct {
    float x, y;
} vec2;

// float Vector 3
typedef struct {
    float x, y, z;
} vec3;

// float Vector 4
typedef struct {
    float x, y, z, w;
} vec4;

// 2x2 float Matrix
typedef struct {
    float entries[4];
} mat2;

// 3x3 float Matrix
typedef struct {
    float entries[9];
} mat3;

// 4x4 float Matrix
typedef struct {
    float entries[16];
} mat4;

// quaternion
typedef struct {
    float w;
    float x, y, z;
} quat;

#define TARGET_X 0b0001
#define TARGET_Y 0b0010
#define TARGET_Z 0b0100
#define TARGET_W 0b1000
#define TARGET_ALL 0b1111

#define AXIS_X 0b001
#define AXIS_Y 0b010
#define AXIS_Z 0b100
#define AXIS_ALL 0b111

// STACK ALLOCATING CONSTRUCTORS

// VECTORS
// vec2 stack allocating constructor
vec2 vec2_new(float x, float y);
// vec3 stack allocating constructor
vec3 vec3_new(float x, float y, float z);
// vec4 stack allocating constructor
vec4 vec4_new(float x, float y, float z, float w);

// SPECIAL VECTORS
// returns a float vector 2 with all components set to 0
vec2 vec2_zero();
// returns a float vector 2 with all components set to 1
vec2 vec2_one();
// returns a float vector 3 with all components set to 0
vec3 vec3_zero();
// returns a float vector 3 with all components set to 1
vec3 vec3_one();
// returns a float vector 4 with all components set to 0
vec4 vec4_zero();
// returns a float vector 4 with all components set to 1
vec4 vec4_one();

// MATRICES
// mat2 stack allocating constructor
mat2 mat2_new(float entries[4]);
// mat3 stack allocating constructor
mat3 mat3_new(float entries[9]);
// mat4 stack allocating constructor
mat4 mat4_new(float entries[16]);

// GETTERS
// gets the given matrix entry at the given row and column and returns the value
float mat2_get(mat2* m, unsigned char row, unsigned char column);
// gets the given matrix entry at the given row and column and returns the value
float mat3_get(mat3* m, unsigned char row, unsigned char column);
// gets the given matrix entry at the given row and column and returns the value
float mat4_get(mat4* m, unsigned char row, unsigned char column);

// SETTERS
// sets the given matrix entry at the given row and column to the specified entry value
void mat2_set(mat2* m, unsigned char row, unsigned char column, float value);
// sets the given matrix entry at the given row and column to the specified entry value
void mat3_set(mat3* m, unsigned char row, unsigned char column, float value);
// sets the given matrix entry at the given row and column to the specified entry value
void mat4_set(mat4* m, unsigned char row, unsigned char column, float value);

// sets the given matrix entries all at once to the given entries array
void mat2_setAll(mat2* m, float entries[4]);
// sets the given matrix entries all at once to the given entries array
void mat3_setAll(mat3* m, float entries[9]);
// sets the given matrix entries all at once to the given entries array
void mat4_setAll(mat4* m, float entries[16]);

// SPECIAL MATRICES
// returns a 2x2 float matrix with all entries set to 0
mat2 mat2_zero();
// returns a 2x2 float identity matrix
mat2 mat2_identity();
// returns a 2x2 float translation matrix based on the given translation vector
// mat2 mat2_translation(vec2 translation);
// returns a 2x2 float rotation matrix based on the given angle value (in degrees)
mat2 mat2_rotation(float angle);
// returns a 2x2 float scaling matrix based on the given scale value
mat2 mat2_scaling(vec2 scaling);

// returns a 3x3 float matrix with all entries set to 0
mat3 mat3_zero();
// returns a 3x3 float identity matrix
mat3 mat3_identity();
// returns a 3x3 float translation matrix based on the given translation vector
// mat3 mat3_translation(vec3 translation);
// returns a 3x3 float rotation matrix based on the given angle value (in degrees)
// axes can either be AXIS_X, AXIS_Y, AXIS_Z, AXIS_ALL or a combination of these given by doing bitwise OR
mat3 mat3_rotation(unsigned char axes, float angle);
// returns a 3x3 float scaling matrix based on the given scale value
mat3 mat3_scaling(vec3 scaling);

// returns a 4x4 float matrix with all entries set to 0
mat4 mat4_zero();
// returns a 4x4 float identity matrix
mat4 mat4_identity();
// returns a 4x4 float translation matrix based on the given translation vector
mat4 mat4_translation(vec3 translation);
// returns a 4x4 float rotation matrix based on the given rotation vector
// axis is a unit vector representing the direction of the rotation axis.
// by default the rotation axis runs through the origin (0, 0, 0),
// meaning that in order to rotate around a different pivot you must first
// translate the object so that the pivot is located at the origin
// (so translate it by the negated pivot position vector)
mat4 mat4_rotation(vec3 axis, float angle);
// returns a 4x4 float rotation matrix based on the given rotation vector as Tait-Bryan angles (pitch, yaw, roll)
mat4 mat4_eulerRotation(vec3 angles);
// returns a 4x4 float scaling matrix based on the given scale value
mat4 mat4_scaling(vec3 scaling);

// returns an orthographic projection matrix given the projection parameters
mat4 matrix_getOrthographicProjection(float left, float right, float bottom, float top, float near, float far);
// returns a perspective projection matrix given the projection parameters
// FOV should be provided in DEGREES
mat4 matrix_getPerspectiveProjection(float width, float height, float fov, float near, float far);

// QUATERNIONS
// quat stack allocating constructor
quat quat_new(float w, float x, float y, float z);

// returns a quaternion with all components set to 0
quat quat_zero();
// returns an identity quaternion
quat quat_identity();
// returns a rotation quaternion based on the given axis direction and angle value
quat quat_rotation(vec3 axis, float angle);

// LINEAR ALGEBRA OPERATIONS

// VECTORS
// sum, diff, scale, dot, cross, inverse, magnitude, normalise (versor)

// VECTOR SUM
// sums two vectors and returns the result
vec2 vec2_sum(vec2 v0, vec2 v1);
// sums two vectors and returns the result
vec3 vec3_sum(vec3 v0, vec3 v1);
// sums two vectors and returns the result
vec4 vec4_sum(vec4 v0, vec4 v1);

// VECTOR DIFFERENCE
// subtracts two vectors and returns the result
vec2 vec2_difference(vec2 v0, vec2 v1);
// subtracts two vectors and returns the result
vec3 vec3_difference(vec3 v0, vec3 v1);
// subtracts two vectors and returns the result
vec4 vec4_difference(vec4 v0, vec4 v1);

// VECTOR SCALE
// scales a vector by the s float parameter and returns the result
vec2 vec2_scale(vec2 v, float s);
// scales a vector by the s float parameter and returns the result
vec3 vec3_scale(vec3 v, float s);
// scales a vector by the s float parameter and returns the result
vec4 vec4_scale(vec4 v, float s);

// VECTOR DOT PRODUCT
// evaluates the dot product between v0 and v1 and returns the result
float vec2_dot(vec2 v0, vec2 v1);
// evaluates the dot product between v0 and v1 and returns the result
float vec3_dot(vec3 v0, vec3 v1);
// evaluates the dot product between v0 and v1 and returns the result
float vec4_dot(vec4 v0, vec4 v1);

// VECTOR CROSS PRODUCT
// evaluates the cross product between v0 and v1 and returns the result
vec3 vec3_cross(vec3 v0, vec3 v1);

// VECTOR INVERSE
// swaps the specified component(s) sign of the given vector and returns the result
// target can either be TARGET_X, TARGET_Y, TARGET_ALL or a combination of these given by doing bitwise OR
vec2 vec2_negate(vec2 v, unsigned char target);
// swaps the specified component(s) sign of the given vector and returns the result
// target can either be TARGET_X, TARGET_Y or TARGET_Z, TARGET_ALL or a combination of these given by doing bitwise OR
vec3 vec3_negate(vec3 v, unsigned char target);
// swaps the specified component(s) sign of the given vector and returns the result
// target can either be TARGET_X, TARGET_Y, TARGET_Z or TARGET_W, TARGET_ALL or a combination of these given by doing bitwise OR
vec4 vec4_negate(vec4 v, unsigned char target);

// VECTOR MAGNITUDE
// evaluates the given vector magnitude and returns the result
float vec2_magnitude(vec2 v);
// evaluates the given vector magnitude and returns the result
float vec3_magnitude(vec3 v);
// evaluates the given vector magnitude and returns the result
float vec4_magnitude(vec4 v);

// VECTOR NORMALIZE
// normalizes the given vector and returns the result
vec2 vec2_normalize(vec2 v);
// normalizes the given vector and returns the result
vec3 vec3_normalize(vec3 v);
// normalizes the given vector and returns the result
vec4 vec4_normalize(vec4 v);

// MATRICES
// sum, diff, scale, mul, (adj, det, rank), transpose, negate (scale by -1)

// MATRIX SUM
// sums two matrices and returns the result
mat2 mat2_sum(mat2 m0, mat2 m1);
// sums two matrices and returns the result
mat3 mat3_sum(mat3 m0, mat3 m1);
// sums two matrices and returns the result
mat4 mat4_sum(mat4 m0, mat4 m1);

// MATRIX DIFFERENCE
// subtracts two matrices and returns the result
mat2 mat2_difference(mat2 m0, mat2 m1);
// subtracts two matrices and returns the result
mat3 mat3_difference(mat3 m0, mat3 m1);
// subtracts two matrices and returns the result
mat4 mat4_difference(mat4 m0, mat4 m1);

// MATRIX SCALE
// scales a matrix by the given s float parameter and returns the result
mat2 mat2_scale(mat2 m, float s);
// scales a matrix by the given s float parameter and returns the result
mat3 mat3_scale(mat3 m, float s);
// scales a matrix by the given s float parameter and returns the result
mat4 mat4_scale(mat4 m, float s);

// MATRIX MULTIPLICATION
// multiplies two matrices and returns the result
mat2 mat2_multiply(mat2 m0, mat2 m1);
// multiplies two matrices and returns the result
mat3 mat3_multiply(mat3 m0, mat3 m1);
// multiplies two matrices and returns the result
mat4 mat4_multiply(mat4 m0, mat4 m1);

// MATRIX TRANSPOSE
// transposes a matrix and returns the result
mat2 mat2_transpose(mat2 m);
// transposes a matrix and returns the result
mat3 mat3_transpose(mat3 m);
// transposes a matrix and returns the result
mat4 mat4_transpose(mat4 m);

// MATRIX NEGATE
// negates a matrix (scales it by -1) and returns the result
mat2 mat2_negate(mat2 m);
// negates a matrix (scales it by -1) and returns the result
mat3 mat3_negate(mat3 m);
// negates a matrix (scales it by -1) and returns the result
mat4 mat4_negate(mat4 m);

// QUATERNIONS
// multiply

// multiplies two quaternions and returns the result
quat quat_multiply(quat q0, quat q1);

// MIXED OPERATIONS
// 2D, 3D
// mul, (translate, rotate, scale)

// MATRIX with VECTOR MULTIPLICATION
// multiplies a matrix by a vector and returns the result
vec2 mat2_vec2_multiply(mat2 m, vec2 v);
// multiplies a matrix by a vector and returns the result
vec3 mat3_vec3_multiply(mat3 m, vec3 v);
// multiplies a matrix by a vector and returns the result
vec4 mat4_vec4_multiply(mat4 m, vec4 v);

// MATRIX to QUATERNION and viceversa
// converts a rotation quaternion to a 4D rotation matrix
mat4 quat_to_mat4(quat q);
// converts a 4D rotation matrix to a rotation quaternion
quat mat4_to_quat(mat4 m);

// OUTPUT
// prints out the given vector (precision specifies the number of decimal digits)
void print_vec2(vec2 v, unsigned int precision);
// prints out the given vector (precision specifies the number of decimal digits)
void print_vec3(vec3 v, unsigned int precision);
// prints out the given vector (precision specifies the number of decimal digits)
void print_vec4(vec4 v, unsigned int precision);

// prints out the given matrix (precision specifies the number of decimal digits)
void print_mat2(mat2 m, unsigned int precision);
// prints out the given matrix (precision specifies the number of decimal digits)
void print_mat3(mat3 m, unsigned int precision);
// prints out the given matrix (precision specifies the number of decimal digits)
void print_mat4(mat4 m, unsigned int precision);

// prints out the given quaternion (precision specifies the number of decimal digits)
void print_quat(quat q, unsigned int precision);

#endif