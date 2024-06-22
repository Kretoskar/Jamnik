#pragma once

class EBO
{
public:
    unsigned int _id;

    EBO(unsigned int* indices, long long size);
    void Init(unsigned int* indices, long long size);
    
    void Bind() const;
    void Delete();
};
