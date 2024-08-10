#pragma once
#include <memory>
#include <string>

#include "Rendering/GLTFLoader.h"

class Mesh;
class Texture;

namespace Jamnik
{
    struct Material;
    class Shader;
    
    class AssetsRegistry
    {
        AssetsRegistry() {}
    
        AssetsRegistry(AssetsRegistry const&) = delete;
        void operator=(AssetsRegistry const &) = delete;
    
    public:
        static AssetsRegistry& GetInstance()
        {
            static AssetsRegistry instance;
            return instance;
        }

        static std::string ReadFile(const char* filename);
        
        void Init();
        void Cleanup();

        std::shared_ptr<Shader> meshShader;
        std::shared_ptr<Shader> lightShader;
        
        std::shared_ptr<Texture> meshDiffuseMap;
        std::shared_ptr<Texture> meshSpecularMap;

        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Mesh> lightMesh;

        std::shared_ptr<Material> meshMaterial;
        std::shared_ptr<Material> lightMaterial;

        std::shared_ptr<GLTFLoader> model;
    };
}