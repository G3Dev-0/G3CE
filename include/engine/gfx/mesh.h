/*
MESH:
A mesh is a collection of vertices. It also has indices that specify how to connect said vertices.
Vertices can then have properties like color, normal and such.
*/

#ifndef MESH_H
#define MESH_H

typedef struct {
    int vao;
    int vbosCount;
    int* vbos;
    int ebo;
    int drawMode;
} Mesh;

// creates the mesh and returns its VAO
// vertices is the vertices position array
// verticesLength is the sizeof() of the vertices position array
// indices is the indices array, specifing the order in which to render the verices
// indicesLength is the sizeof() of the indices array
// drawMode is the OpenGL mode to draw the verices (GL_TRIANGLES, GL_QUADS, ...)
// YOU MUST FREE THE VAO BY CALLING mesh_destroy()
Mesh* mesh_create(float* vertices, unsigned int verticesLength, unsigned int* indices, unsigned int indicesLength, int drawMode);

// creates a VBO and associates it to a vertex attribute of type int buffer to the specified mesh
// attribLocation is the location of the attribute in the shader
// size is the number of components for each vertex attribute (e.g.: 3 for 3D position, 4 for RGBA colors)
// dataLength is the sizeof() of the data array
void mesh_addVertexAttributeFloat(Mesh* mesh, int attribLocation, int size, float* data, unsigned int dataLength);

// destroies the given mesh (VAO)
void mesh_destroy(Mesh* mesh);

// draws the given mesh using the given shader (programID)
void mesh_draw(Mesh* mesh, int shader);

#endif