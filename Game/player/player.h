#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Utitlity/shader/shader.h"
#include "../../Utitlity/spriteRenderer/spriteRenderer.h"
#include<iostream>
#include<vector>

#include "../global.h"

class Player{
    
    public:

        SpriteRenderer sprite;
        glm::vec3 position;
        bool dead;
        float deltaSpeed;
        float width;
        hitBox myHitBox;    

        void init(glm::vec3 targetPosition);
        void render(Shader shader, Texture texture);   

        void move(float deltaX,float deltaY);
        void getHitBox();
        void getNode();

};

#endif