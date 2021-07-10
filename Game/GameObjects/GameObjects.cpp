#include "GameObjects.h"


void Objects :: init(glm::vec3 position, int row, int col, int type)
{   if(type == 0)
        this->width = 0.2;
    else this->width = 0.16;
    sprite.initRenderData(this->width);
    this->position = position;
    this->row = row;
    this->col =col;
    check = false;
    this->type = type;
    
}

void Objects :: render(Shader shader, Texture texture)
{   
    
    if(this->type == 1){
        sprite.DrawSprite(texture, this->position,shader,(float)glfwGetTime());
    }
    else{
        sprite.DrawSprite(texture, this->position,shader);
    }
}
