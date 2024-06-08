#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Texture;

namespace Jamnik
{
    class Shader
    {
        std::string _fragmentFilePath;
        std::string _vertexFilePath;
        std::unordered_map<std::string, int> _uniformLocationCache;
    
        unsigned int _id;
    
    public:
        Shader(std::string fragmentFilePath, std::string vertexFilePath);
        ~Shader();

        void Bind() const;

        void Delete();
        
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniform1f(const std::string& name, float v0);
        void SetUniform2f(const std::string& name, float v0, float v1);
        void SetUniform1i(const std::string& name, int v0);

        void SetUniformMat4f(const std::string& name, const glm::mat4& mat);

        void AssignBaseTexture(Texture& texture);
        // TODO: Add the same for normal, specular etc.

        void SetModelMatrix(glm::mat4 m);
        void SetViewMatrix(glm::mat4 m);
        void SetProjectionMatrix(glm::mat4 m);
        
    private:
        int GetUniformLocation(const std::string& name);
        unsigned int CreateShader();
        unsigned int CompileShader(unsigned int type, const std::string& source);
    };
}
