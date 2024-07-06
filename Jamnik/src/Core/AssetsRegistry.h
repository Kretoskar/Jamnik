#pragma once
#include <memory>

class Texture;

namespace Jamnik
{
    class Shader;
    
    class AssetsRegistry
    {
    public:
        void Init();
        void Cleanup();

        std::shared_ptr<Shader> meshShader;
        std::shared_ptr<Shader> lightShader;
        
        std::shared_ptr<Texture> meshDiffuseMap;
        std::shared_ptr<Texture> meshSpecularMap;
    };
}