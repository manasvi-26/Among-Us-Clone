#include"imposter.h"

void Imposter :: init(glm::vec3 targetPosition)
{
    this->width = 0.14;
    sprite.initRenderData(this->width);
    this->position = targetPosition;
    this->dead = false;
}

void Imposter :: render(Shader shader, Texture texture)
{
    sprite.DrawSprite(texture,this->position,shader);
}


void Imposter :: move(glm::vec3 newPosition)
{
    this->position = newPosition;
}

void Imposter :: kill()
{
    this->dead = true;
    this->position = glm::vec3(-100,100,0.f);
}

