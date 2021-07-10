#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
class Texture
{
    public:
        unsigned int ID;
        unsigned int Width, Height;
        unsigned int Internal_Format;
        unsigned int Image_Format; 


        Texture();
        void Generate(unsigned int width, unsigned int height, unsigned char* data, bool aplha);
        void Bind();

};



#endif