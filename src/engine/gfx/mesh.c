/*
MESH:
A mesh is a collection of vertices. It also has indices that specify how to connect said vertices.
Vertices can then have properties like color, normal and such.
*/

#include <stdlib.h>

#include <glad/glad.h>

#include "engine/gfx/shader.h"

#include "engine/gfx/mesh.h"

// creates the mesh and returns its VAO
// vertices is the vertices position array
// verticesLength is the sizeof() of the vertices position array
// indices is the indices array, specifing the order in which to render the verices
// indicesLength is the sizeof() of the indices array
// drawMode is the OpenGL mode to draw the verices (GL_TRIANGLES, GL_QUADS, ...)
// YOU MUST FREE THE VAO BY CALLING mesh_destroy()
Mesh* mesh_create(float* vertices, unsigned int verticesLength, unsigned int* indices, unsigned int indicesLength, int drawMode) {
    // generate VAO
    int vao;
    glGenVertexArrays(1, &vao);

    Mesh* mesh = (Mesh*) malloc(sizeof(Mesh));
    mesh->vao = vao;
    mesh->vbosCount = 0;
    // allocate some memory to the vbos array
    mesh->vbos = (int*) malloc(0);

    // bind the positions VBO and the EBO to the VAO

    // bind VAO
    glBindVertexArray(vao);

    // positions VBO
    mesh_addVertexAttributeFloat(mesh, 0, 3, vertices, verticesLength);

    // EBO
    // generate EBO
    int ebo;
    glGenBuffers(1, &ebo);
    // bind the EBO to the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength, indices, GL_STATIC_DRAW);

    mesh->ebo = ebo;
    
    // unbind the VAO BEFORE UNBINDING THE VBOs AND THE EBO,
    // OTHERWISE IT WILL KEEP IN MEMORY THAT IT HAS TO UNBIND
    // VBOs and EBO BEFORE CALLING glDrawElements();
    glBindVertexArray(0);

    // unbind the VBOs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // unbind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return mesh;
}

// creates a VBO and associates it to a vertex attribute of type int buffer to the specified mesh
// attribLocation is the location of the attribute in the shader
// size is the number of components for each vertex attribute (e.g.: 3 for 3D position, 4 for RGBA colors)
// dataLength is the sizeof() of the data array
void mesh_addVertexAttributeFloat(Mesh* mesh, int attribLocation, int size, float* data, unsigned int dataLength) {
    // generate VBO
    int vbo;
    glGenBuffers(1, &vbo);

    // must bind the VBO now, because glVertexAttribPointer() associates the attribute location to the currently bound VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dataLength, data, GL_STATIC_DRAW);

    // associate the attribute location (in the shader)
    glVertexAttribPointer(attribLocation, size, GL_FLOAT, GL_FALSE, size * sizeof(float), NULL);
    glEnableVertexAttribArray(attribLocation);

    // add the vbo to the mesh vbos and also update the vbosCount
    mesh->vbosCount++;
    mesh->vbos = (int*) realloc(mesh->vbos, (mesh->vbosCount) * sizeof(int));
    mesh->vbos[(mesh->vbosCount) - 1] = vbo;
}

// destroies the given mesh
void mesh_destroy(Mesh* mesh) {
    // delete the VBOs
    for (int i = 0; i < mesh->vbosCount; i++) {
        glDeleteBuffers(GL_ARRAY_BUFFER, &(mesh->vbos[i]));
    }

    // delete the EBO
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &(mesh->ebo));

    // delete the VAO
    glDeleteVertexArrays(1, &(mesh->vao)); // &mesh->vbos[i] is also correct, as the arrow operator has priority over the address-of operator, but it's easier to read

    // finally free mesh
    free(mesh);
}

// draws the given mesh using the given shader (programID)
void mesh_draw(Mesh* mesh, int shader) {
    shader_use(shader);
    // now when we want to render that particular VAO we just do
    // bind the VAO
    glBindVertexArray(mesh->vao);
    // args: mode (how to interpret the vericies data), initial offset, vertex count
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    // unbind the VAO for good practive
    glBindVertexArray(0);
}