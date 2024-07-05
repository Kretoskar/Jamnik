#include "Material.h"
#include "Shaders/Shader.h"
#include "Texture.h"

namespace Jamnik
{
    Material::Material(Texture* InDiffuseMap, Texture* InSpecularMap, Jamnik::Shader& InShader)
        : DiffuseMap(InDiffuseMap), SpecularMap(InSpecularMap), Shader(&InShader)
    {
        if (DiffuseMap)
        {
            Shader->AssignDiffuseMap(*DiffuseMap);
        }

        if (SpecularMap)
        {
            Shader->AssignSpecularMap(*SpecularMap);
        }
    }

    void Material::Bind()
    {
        if (Shader)
        {
            Shader->Bind();
        }
        
        if (DiffuseMap)
        {
            DiffuseMap->Bind();
        }

        if (SpecularMap)
        {
            SpecularMap->Bind();
        }
    }
}

