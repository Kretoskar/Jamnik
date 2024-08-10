#pragma once
#include <vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "json.h"
#include "Material.h"
#include "Texture.h"
#include "Vertex.h"

using json = nlohmann::json;

class Mesh;

class GLTFLoader
{
public:
    GLTFLoader(const char* file);

    //TODO: Static func for loading instead?
    
    std::vector<Mesh> meshes;
    
private:
    std::vector<float> GetFloats(json accessor);
    std::vector<unsigned> GetIndices(json accessor);

    void TraverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

    std::vector<Vertex> AssembleVertices
    (
        std::vector<glm::vec3> positions, 
        std::vector<glm::vec3> normals, 
        std::vector<glm::vec2> texUVs
    );

    void LoadMesh(unsigned int indMesh);
    
    // Helps with the assembly from above by grouping floats
    std::vector<glm::vec2> GroupFloatsVec2(std::vector<float> floatVec);
    std::vector<glm::vec3> GroupFloatsVec3(std::vector<float> floatVec);
    std::vector<glm::vec4> GroupFloatsVec4(std::vector<float> floatVec);
    
    const char* file;
    std::vector<unsigned char> data;
    json JSON;
};