#pragma once
#include <vector>

#include "Vertex.h"

class VBO
{
public:
    unsigned int _id;

    VBO(float* vertices, long long size);
    VBO(const std::vector<Vertex>& vertices);
    void Init(float* vertices, long long size);
    void Init(const std::vector<Vertex>& vertices);

    void Bind() const;
    void Delete();
};
