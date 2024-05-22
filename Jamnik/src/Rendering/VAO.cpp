#include "VAO.h"

#include <glad/glad.h>

#include "VBO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &_id);
}

void VAO::LinkVBO(const VBO& vbo, unsigned layout)
{
    vbo.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
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
