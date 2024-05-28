#pragma once

class VBO;

class VAO
{
public:
    unsigned int _id;
    VAO();

    void LinkAttrib(const VBO& vbo, unsigned layout, int numComponents, unsigned type, int stride, void* offset);
    void Bind();
    void Delete();
};
