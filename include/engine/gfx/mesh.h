#ifndef MESH_H
#define MESH_H

/*
MESH:
Handles mesh creation and destruction
*/

typedef struct {
    int vao;
    int vbo;
    int ebo;
    int drawMode;
    int lastOffset;
    int indicesLength;
    int stride;
} Mesh;

/*
Creates a new mesh object and returns a pointer to it.
You MUST call mesh_destroy(Mesh*) once the mesh is not used anymore
in order to free the allocated memory
All the vertex data must be put into the same vertices array
Arguments:
    - vertices (float*): pointer to float array containing ALL the vertex data (positions, colors, UVs, normals, etc...)
    - verticesSize (int): sizeof(vertices)
    - indices (unsigned int*): pointer to integer array containing the indices that specify the order in which the vertices must be rendered
    - indicesSize (int): sizeof(indices)
    - vertexLength (int): the number of floats that defines a vertex (e.g.: 3 for 3D position + 4 for RGBA color = 7)
    - drawMode (int): the drawing mode OpenGL has to use (GL_TRIANGLES, GL_QUADS, etc...)
Returns:
    The pointer to the mesh struct that has been created. It points to dynamically allocated memory,
    so you MUST call mesh_destroy(Mesh*) that handles the free() procedure
*/
Mesh* mesh_create(float* vertices, int verticesSize, unsigned int* indices, int indicesSize, int vertexLength, int drawMode);

/*
Registers a vertex attribute of type float for the given mesh.
Arguments:
    - mesh (Mesh*): the pointer to the mesh to associate the new vertex float attribute
    - attributeLocation (int): the attribute location in the shader
    - size (int): number of floats that composes a vertex attribute (e.g.: 2 for UV coordinates, 3 for 3D positions, 4 for RGBA colors)
*/
void mesh_registerVertexAttribute(Mesh* mesh, int attributeLocation, int size);

/*
Destroys the given mesh object.
Arguments:
    - mesh (Mesh*): the mesh to destroy
*/
void mesh_destroy(Mesh* mesh);

#endif