#include "player.h"

void Player :: init(glm::vec3 targetPosition)
{
    this->dead = false;
    this->width = 0.14;
    sprite.initRenderData(this->width);
    this->position = targetPosition;
} 


void Player :: render(Shader shader, Texture texture)
{   
    sprite.DrawSprite(texture,this->position,shader);
}

void Player :: move(float deltaX, float deltaY)
{
    this->position += glm::vec3(deltaX, deltaY, 0.0f);
}


void Player :: getHitBox()
{
    float extra = 0.0007;
    myHitBox.topLeft = make_pair(position.x - width - extra, position.y + width + extra);
    myHitBox.bottomLeft = make_pair(position.x - width - extra, position.y - width - extra);
    myHitBox.topRight = make_pair(position.x + width + extra, position.y + width +extra);
    myHitBox.bottomRight = make_pair(position.x + width + extra, position.y - width - extra);
}

