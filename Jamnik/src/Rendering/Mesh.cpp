#include "Mesh.h"

#include <glad/glad.h>

#include "EBO.h"
#include "Material.h"
#include "VBO.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, Jamnik::Material* material)
    : vertices(vertices), indices(indices), material(material)
{
    vao.Bind();

    const VBO vbo = VBO(vertices);
    const EBO ebo = EBO(indices);
    
    // position
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    //normals
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    // color
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    // UV
    vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
}

Mesh::~Mesh()
{
    vao.Delete();
}

void Mesh::Draw()
{
    material->Bind();
    vao.Bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
