#pragma once
#include <string>

#include <glad/glad.h>

namespace Jamnik
{
    class Shader;
}

class Texture
{
    unsigned _id;
    unsigned _type;
    int _width, _height, _numColCh;

public:
    Texture(std::string path, unsigned slot, unsigned format, unsigned pixelType = GL_UNSIGNED_BYTE, unsigned texType = GL_TEXTURE_2D);
    void Bind();
    void Delete();   
};
