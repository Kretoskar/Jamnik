#include "Shader.h"

#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Logger.h"
#include "Rendering/Texture.h"

Jamnik::Shader::Shader(std::string fragmentFilePath, std::string vertexFilePath)
    : _fragmentFilePath(std::move(fragmentFilePath)), _vertexFilePath(std::move(vertexFilePath))
{
    _id = CreateShader();
}

Jamnik::Shader::~Shader()
{
    glDeleteProgram(_id);
}

void Jamnik::Shader::Bind() const
{
    glUseProgram(_id);
}

void Jamnik::Shader::Delete()
{
    glDeleteProgram(_id);
}

void Jamnik::Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    Bind();
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Jamnik::Shader::SetUniform1f(const std::string& name, float v0)
{
    Bind();
    glUniform1f(GetUniformLocation(name), v0);
}

void Jamnik::Shader::SetUniform2f(const std::string& name, float v0, float v1)
{
    Bind();
    glUniform2f(GetUniformLocation(name), v0, v1);
}

void Jamnik::Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    Bind();
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Jamnik::Shader::SetUniform1i(const std::string& name, int v0)
{
    Bind();
    glUniform1i(GetUniformLocation(name), v0);
}

void Jamnik::Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
    Bind();
    // pass with no transpose bcs both glm and opengl use column major matrices
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);   
}

void Jamnik::Shader::AssignDiffuseMap(Texture& texture)
{
    Bind();
    texture.Bind();
    SetUniform1i("diffuseMap", 0);
}

void Jamnik::Shader::AssignSpecularMap(Texture& texture)
{
    Bind();
    texture.Bind();
    SetUniform1i("specularMap", 1);
}

void Jamnik::Shader::SetModelMatrix(glm::mat4 m)
{
    Bind();
    SetUniformMat4f("model", m);
}

void Jamnik::Shader::SetVPMatrix(glm::mat4 m)
{
    Bind();
    SetUniformMat4f("viewProj", m);
}

void Jamnik::Shader::SetCameraPosition(glm::vec3 pos)
{
    Bind();
    SetUniform3f("cameraPos", pos.x, pos.y, pos.z);
}

void Jamnik::Shader::SetLightPosition(glm::vec3 pos)
{
    Bind();
    SetUniform3f("lightPos", pos.x, pos.y, pos.z);
}

void Jamnik::Shader::SetLightColor(glm::vec4 color)
{
    Bind();
    SetUniform4f("lightColor", color.x, color.y, color.z, color.w);
}

int Jamnik::Shader::GetUniformLocation(const std::string& name)
{
    Bind();
    if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
    {
        return _uniformLocationCache[name];
    }

    const int location = glGetUniformLocation(_id, name.c_str());
    _uniformLocationCache[name] = location;

    if (location < 0)
    {
        JAMNIK_LOG_WARNING("Trying to retrieve invalid uniform location of name %s", name)
    }
    
    return location;
}

unsigned Jamnik::Shader::CreateShader()
{
    std::ifstream fileVert(_vertexFilePath);
    std::stringstream SSvertSource;
    SSvertSource << fileVert.rdbuf();
    std::string vertSource = SSvertSource.str();

    std::ifstream fileFrag(_fragmentFilePath);
    std::stringstream SSfragSource;
    SSfragSource << fileFrag.rdbuf();
    std::string fragSource = SSfragSource.str();
    
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned Jamnik::Shader::CompileShader(unsigned type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* scr = source.c_str();
    glShaderSource(id, 1, &scr, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = static_cast<char*>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(id, length, &length, message);
        
        JAMNIK_LOG_ERROR(message)
        glDeleteShader(id);
        
        return 0;
    }
    
    return id;
}
