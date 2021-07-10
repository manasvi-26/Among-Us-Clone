#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {

    public:
        unsigned int ID;

        Shader()
        {}

        void compile(const char* vShaderCode,const char* fShaderCode);
        void use();
        void setMatrix4(const char *name, const glm::mat4 &matrix );

    private :
        void checkCompileErrors(unsigned int shader,string type);

};

#endif // !SHADER_H
