#include "spriteRenderer.h"


void SpriteRenderer ::DrawSprite(Texture &texture, glm::vec3 position, Shader & shader)
{
    this->shader = shader;
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model= glm::translate(model,position);
    this->shader.setMatrix4("model", model);


    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}


void SpriteRenderer ::DrawSprite(Texture &texture, glm::vec3 position, Shader & shader,float rotation)
{
    this->shader = shader;
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model= glm::translate(model,position);
    model = glm::rotate(model,rotation,glm::vec3(0.0f,1.0f,0.0f));
    this->shader.setMatrix4("model", model);
    

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}
 

void SpriteRenderer::initRenderData(float width)
{

    unsigned int VBO;
    float vertices[] = {
        // positions          // colors           // texture coords
         width,  width, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         width, -width, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -width, -width, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -width,  width, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));   
    glEnableVertexAttribArray(2);
    
    //unbinds VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0);
}

