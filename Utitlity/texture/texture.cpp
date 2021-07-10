#include <iostream>

#include "texture.h"


Texture::Texture()
{
    glGenTextures(1, &this->ID);
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data, bool alpha)
{
  
    if(alpha == true){
        Internal_Format = GL_RGBA;
        Image_Format = GL_RGBA;
    }
    if(alpha == false){
        Internal_Format = GL_RGB;
        Image_Format = GL_RGB;
    }

    this->Width = width;
    this->Height = height;
    

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}