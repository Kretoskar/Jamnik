#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texUV;
in vec3 normal;
in vec3 pos;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

vec4 PointLight()
{
    vec3 lightVec = lightPos - pos;
    float dist = length(lightVec);
    float quadraticTerm = 0.001f;
    float linearTerm = 0.005f;
    float lightIntensity = 1.0f / (quadraticTerm * dist * dist + linearTerm * dist + 1.0f);
    
    // ambient lighting
    float ambient = 0.20f;

    // diffuse lighting
    vec3 normal = normalize(normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    // specular lighting
    float specular = 0.0f;
    if (diffuse > 0.0f)
    {
        float specularLight = 0.50f;
        vec3 viewDirection = normalize(cameraPos - pos);
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        vec3 halfwayVec = normalize(viewDirection + lightDirection);
        float specAmount = pow(max(dot(viewDirection, halfwayVec), 0.0f), 8);
        float specular = specAmount * specularLight;
    }

    // outputs final color
    return (texture(diffuseMap, texUV) * (diffuse * lightIntensity + ambient) + texture(specularMap, texUV).r * specular * lightIntensity) * lightColor;
}

void main()
{
    FragColor = PointLight();
}