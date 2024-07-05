#pragma once

class Texture;

namespace Jamnik
{
    class Shader;
    
    struct Material
    {
        Material() = default;
        Material(Texture* InDiffuseMap, Texture* InSpecularMap, Shader& InShader);
        void Bind();
        
        Texture* DiffuseMap;
        Texture* SpecularMap;
        Shader* Shader;
    };
}