#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexUV;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 texUV;

out vec3 normal;
out vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    pos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = proj * view * vec4(pos, 1.0f);
    color = aColor;
    texUV = aTexUV;
    
    normal = aNormal;
}