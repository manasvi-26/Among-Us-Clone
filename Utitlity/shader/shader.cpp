#include "shader.h"

void Shader :: compile(const char* vShaderCode,const char* fShaderCode)
{
    

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment,"FRAGMENT");
    
    ID = glCreateProgram();
    
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
        
}


void Shader :: use() 
{ 
    glUseProgram(ID); 
}
        
void Shader :: setMatrix4(const char *name, const glm::mat4 &matrix )
{
    this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader :: checkCompileErrors(unsigned int shader,string type)
{
    int success;
    char error_message[512];

    if(type == "PROGRAM"){
        glGetProgramiv(shader,GL_LINK_STATUS,&success);
        if(!success){
            glGetProgramInfoLog(shader,sizeof(error_message),NULL,error_message);
            cout << error_message << endl;
            cout << "LINK FAILED :  " << type << endl;
        }

    }
    else{
        glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
        if(!success){
            glGetShaderInfoLog(shader,sizeof(error_message),NULL,error_message);
            cout << error_message << endl;
            cout << "COMPILE FAILED :  " << type << endl;
        }
    }

}
