#include "EBO.h"
#include <glad/glad.h>

EBO::EBO(unsigned* indices, long long size)
{
    Init(indices, size);
}

EBO::EBO(const std::vector<unsigned>& indices)
{
    Init(indices);
}

void EBO::Init(const std::vector<unsigned>& indices)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
}

void EBO::Init(unsigned* indices, long long size)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void EBO::Delete()
{
    glDeleteBuffers(1, &_id);
}
