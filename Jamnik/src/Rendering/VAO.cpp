#include "VAO.h"

#include <glad/glad.h>

#include "VBO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &_id);
}

void VAO::LinkAttrib(const VBO& vbo, unsigned layout, int numComponents, unsigned type, int stride, void* offset)
{
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}

void VAO::Bind()
{
    glBindVertexArray(_id);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &_id);
}
