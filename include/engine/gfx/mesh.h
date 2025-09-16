#ifndef MESH_H
#define MESH_H

/*
MESH:
Handles mesh creation and destruction
*/

typedef struct {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int drawMode;
    unsigned int lastOffset;
    unsigned int indicesLength;
    unsigned int stride;
    unsigned int texture;
    unsigned int textureUnit;
} Mesh;

// creates a stack allocated mesh and returns it. This does not need to be destroyed
Mesh mesh_new(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize, unsigned int vertexLength, unsigned int drawMode);

/*
Creates a new mesh object and returns a pointer to it.
You MUST call mesh_destroy(Mesh*) once the mesh is not used anymore
in order to free the allocated memory
All the vertex data must be put into the same vertices array
Parameters:
    - vertices (float*): pointer to float array containing ALL the vertex data (positions, colors, UVs, normals, etc...)
    - verticesSize (unsigned int): sizeof(vertices)
    - indices (unsigned int*): pointer to integer array containing the indices that specify the order in which the vertices must be rendered
    - indicesSize (unsigned int): sizeof(indices)
    - vertexLength (unsigned int): the number of floats that defines a vertex (e.g.: 3 for 3D position + 4 for RGBA color = 7)
    - drawMode (unsigned int): the drawing mode OpenGL has to use (GL_TRIANGLES, GL_QUADS, etc...)
Returns:
    The pointer to the mesh struct that has been created. It points to dynamically allocated memory,
    so you MUST call mesh_destroy(Mesh*) that handles the free() procedure
*/
Mesh* mesh_create(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize, unsigned int vertexLength, unsigned int drawMode);

/*
Destroys the given mesh object.
Parameters:
    - mesh (Mesh*): the mesh to destroy
*/
void mesh_destroy(Mesh* mesh);

/*
Registers a vertex attribute of type float for the given mesh.
Parameters:
    - mesh (Mesh*): the pointer to the mesh to associate the new vertex float attribute
    - attributeLocation (unsigned int): the attribute location in the shader
    - size (unsigned int): number of floats that composes a vertex attribute (e.g.: 2 for UV coordinates, 3 for 3D positions, 4 for RGBA colors)
*/
void mesh_registerVertexAttribute(Mesh* mesh, unsigned int attributeLocation, unsigned int size);

/*
Assings a texture to a given mesh via a texture id (this means that the texture will be automatically bound when rendering the mesh via renderer_renderMesh()).
Parameters:
    - texture (unsigned int): the texture id
    - unit (unsigned int): the texture unit to attach the texture to
*/
void mesh_assignTexture(Mesh* mesh, unsigned int texture, unsigned int unit);

#endif