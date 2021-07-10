#include "button.h"

void Button :: init(glm::vec3 position, int row, int col, bool Type)
{
    this->width = 0.16;
    sprite.initRenderData(this->width);
    this->position = position;
    this->row = row;
    this->col =col;
    check = false;
    this->buttonType =Type; 
}

void Button :: render(Shader shader, Texture texture)
{   
    sprite.DrawSprite(texture, this->position,shader);
}

void Button :: move(glm::vec3 position)
{
    this->position = position;
    this->row = 100;
    this->col = 100;
}