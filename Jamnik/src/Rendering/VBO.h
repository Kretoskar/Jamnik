#pragma once

class VBO
{
public:
    unsigned int _id;

    VBO(float* vertices, long long size);
    void Init(float* vertices, long long size);

    void Bind() const;
    void Delete();
};
