#pragma once
#include <vector>

class EBO
{
public:
    unsigned int _id;
    
    EBO(unsigned int* indices, long long size);
    EBO(const std::vector<unsigned>& indices);
    void Init(const std::vector<unsigned>& indices);
    void Init(unsigned int* indices, long long size);
    
    void Bind() const;
    void Delete();
};
