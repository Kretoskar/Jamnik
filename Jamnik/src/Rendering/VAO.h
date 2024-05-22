#pragma once

class VBO;

class VAO
{
public:
    unsigned int _id;
    VAO();

    void LinkVBO(const VBO& vbo, unsigned int layout);
    void Bind();
    void Delete();
};
