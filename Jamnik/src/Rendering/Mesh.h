#pragma once
#include <memory>
#include <vector>

#include "Material.h"
#include "VAO.h"

struct Vertex;

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    Jamnik::Material* material;

    // Initializes the mesh
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, Jamnik::Material* material);
    ~Mesh();
    
    void Draw();
    
private:
    VAO vao;
};