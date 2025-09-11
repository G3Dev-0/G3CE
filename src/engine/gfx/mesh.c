/*
MESH:
Handles mesh creation and destruction
*/

#include <stdlib.h>
#include <glad/glad.h>

#include "engine/utils/console.h"

#include "engine/gfx/mesh.h"

/*
Creates a new mesh object and returns a pointer to it.
You MUST call mesh_destroy(Mesh*) once the mesh is not used anymore
in order to free the allocated memory
All the vertex data must be put into the same vertices array
Arguments:
    - vertices (float*): pointer to float array containing ALL the vertex data (positions, colors, UVs, normals, etc...)
    - verticesSize (int): sizeof(vertices)
    - indices (int*): pointer to integer array containing the indices that specify the order in which the vertices must be rendered
    - indicesSize (int): sizeof(indices)
    - vertexLength (int): the number of floats that defines a vertex (e.g.: 3 for 3D position + 4 for RGBA color = 7)
    - drawMode (int): the drawing mode OpenGL has to use (GL_TRIANGLES, GL_QUADS, etc...)
Returns:
    The pointer to the mesh struct that has been created. It points to dynamically allocated memory,
    so you MUST call mesh_destroy(Mesh*) that handles the free() procedure
*/
Mesh* mesh_create(float* vertices, int verticesSize, unsigned int* indices, int indicesSize, int vertexLength, int drawMode) {
    Mesh* mesh = (Mesh*) malloc(sizeof(Mesh));
    if (mesh == NULL) {
        console_error("Failed to allocate memory for mesh creation.");
        return NULL;
    }

    // set some usefull mesh variable values
    mesh->lastOffset = 0;
    mesh->drawMode = drawMode;
    mesh->indicesLength = indicesSize / sizeof(int);
    mesh->stride = vertexLength * sizeof(float);

    // generate VAO and assign it to the mesh
    int vao;
    glGenVertexArrays(1, &vao);
    mesh->vao = vao;

    // bind the mesh VAO
    glBindVertexArray(vao);

    // generate VBO and assign it to the mesh
    int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // generate EBO and assign it to the mesh
    int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    // unbind the mesh VAO
    glBindVertexArray(0);

    // unbind the VBO and the EBO ONLY AFTER UNBINDING THE VAO,
    // otherwise the VBO and EBO unbinding operation gets registered into the VAO
    // and nothing renders
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mesh->vbo = vbo;
    mesh->ebo = ebo;

    return mesh;
}

/*
Registers a vertex attribute of type float for the given mesh.
Arguments:
    - mesh (Mesh*): the pointer to the mesh to associate the new vertex float attribute
    - attributeLocation (int): the attribute location in the shader
    - size (int): number of floats that composes a vertex attribute (e.g.: 2 for UV coordinates, 3 for 3D positions, 4 for RGBA colors)
*/
void mesh_registerVertexAttribute(Mesh* mesh, int attributeLocation, int size) {
    // bind the VAO
    glBindVertexArray(mesh->vao);
    // bind the VBO (otherwise the attribute binding won't work)
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

    // calculate the stride for this vertex attribute
    int attributeSize = size * sizeof(float);
    // register the new vertex attribute
    glVertexAttribPointer(attributeLocation, size, GL_FLOAT, GL_FALSE, mesh->stride, (void*) (mesh->lastOffset));
    glEnableVertexAttribArray(attributeLocation);

    // update the last offset to handle offsets automatically
    mesh->lastOffset += attributeSize;

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*
Destroys the given mesh object.
Arguments:
    - mesh (Mesh*): the mesh to destroy
*/
void mesh_destroy(Mesh* mesh) {
    glDeleteBuffers(GL_ARRAY_BUFFER, &(mesh->vbo));
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &(mesh->ebo));
    glDeleteVertexArrays(1, &(mesh->vao));

    free(mesh);
}