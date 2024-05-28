#include "Texture.h"

#include <glad/glad.h>

#include "stb_image.h"

Texture::Texture(std::string path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* _bytes = stbi_load(path.c_str(), &_width, &_height, &_numColCh, 0);
    glGenTextures(1, &_id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(_bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::Delete()
{
    glDeleteTextures(1, &_id);
}
