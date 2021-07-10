#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;


Shader ResourceManager::LoadShader(const char* vertexPath, const char* fragmentPath,string name)
{
    
    string vertexCode;
    string fragmentCode;

    ifstream vertexFile;
    ifstream fragmentFile;

    vertexFile.exceptions( ifstream::badbit | ifstream :: failbit);
    fragmentFile.exceptions( ifstream::badbit | ifstream :: failbit);

    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        
        stringstream vertexStream, fragmentStream;
        
        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();
        
        vertexFile.close();
        fragmentFile.close();
        
        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    
    }
    catch(ifstream :: failure& e){
        cout << "Failed to read File" << endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    

    Shader shader;
    shader.compile(vShaderCode, fShaderCode);

    Shaders[name] = shader;

    return Shaders[name];
}

Shader ResourceManager::GetShader(string name)
{
    return Shaders[name];
}

Texture ResourceManager::LoadTexture(const char *file,string name, bool alpha)
{
    Texture texture;

    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if(data){
        texture.Generate(width, height, data, alpha);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    stbi_image_free(data);

    Textures[name] = texture;
    return Textures[name];
}

Texture ResourceManager::GetTexture(string name)
{
    return Textures[name];
}
