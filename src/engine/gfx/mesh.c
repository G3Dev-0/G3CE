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
Mesh* mesh_create(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize, unsigned int vertexLength, unsigned int drawMode) {
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
    mesh->texture = 0; // by default no texture is assigned

    // generate VAO and assign it to the mesh
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    mesh->vao = vao;

    // bind the mesh VAO
    glBindVertexArray(vao);

    // generate VBO and assign it to the mesh
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // generate EBO and assign it to the mesh
    unsigned int ebo;
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
Destroys the given mesh object.
Parameters:
    - mesh (Mesh*): the mesh to destroy
*/
void mesh_destroy(Mesh* mesh) {
    glDeleteBuffers(GL_ARRAY_BUFFER, &(mesh->vbo));
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &(mesh->ebo));
    glDeleteVertexArrays(1, &(mesh->vao));

    if (mesh->texture > 0) glDeleteTextures(1, &(mesh->texture));

    free(mesh);
}

/*
Registers a vertex attribute of type float for the given mesh.
Parameters:
    - mesh (Mesh*): the pointer to the mesh to associate the new vertex float attribute
    - attributeLocation (unsigned int): the attribute location in the shader
    - size (unsigned int): number of floats that composes a vertex attribute (e.g.: 2 for UV coordinates, 3 for 3D positions, 4 for RGBA colors)
*/
void mesh_registerVertexAttribute(Mesh* mesh, unsigned int attributeLocation, unsigned int size) {
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
Assings a texture to a given mesh via a texture id (this means that the texture will be automatically bound when rendering the mesh via renderer_renderMesh()).
Parameters:
    - texture (unsigned int): the texture id
    - unit (unsigned int): the texture unit to attach the texture to
*/
void mesh_assignTexture(Mesh* mesh, unsigned int texture, unsigned int unit) {
    if (unit > 32) {
        console_warning("Invalid texture unit for %u. There are a total number of 32 texture units", unit);
        return;
    }
    mesh->texture = texture;
    mesh->textureUnit = unit;
}