#include "VBO.h"

#include <glad/glad.h>

VBO::VBO(float* vertices, long long size)
{
    Init(vertices, size);
}

VBO::VBO(const std::vector<Vertex>& vertices)
{
    Init(vertices);
}

void VBO::Init(float* vertices, long long size)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Init(const std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VBO::Delete()
{
    glDeleteBuffers(1, &_id);
}
