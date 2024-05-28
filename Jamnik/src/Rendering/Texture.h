#pragma once
#include <string>

class Texture
{
    unsigned _id;
    int _width, _height, _numColCh;

public:
    Texture(std::string path);
    void Bind();
    void Delete();   
};
