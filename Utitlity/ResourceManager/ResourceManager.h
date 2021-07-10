#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "../texture/texture.h"
#include "../shader/shader.h"

class ResourceManager
{
    public:

        ResourceManager() { }  

        std::map<std::string, Shader>  Shaders;
        std::map<std::string, Texture> Textures;
         
        Shader LoadShader(const char *vShaderFile, const char *fShaderFile,std::string name);
        Shader GetShader(std::string name);
         
        Texture LoadTexture(const char *file,std::string name, bool alpha);
        Texture GetTexture(std::string name);

    private:
    
              
};

#endif