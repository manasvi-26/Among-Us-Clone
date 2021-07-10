#ifndef IMPOSTER_H
#define IMPOSTER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Utitlity/shader/shader.h"
#include "../../Utitlity/spriteRenderer/spriteRenderer.h"
#include<iostream>
#include<vector>




class Imposter {
    public :
        bool dead;
        glm::vec3 position;
        float width;
        SpriteRenderer sprite;

        void init(glm::vec3 targetPosition);
        void render(Shader shader, Texture texture);   

        
        void move(glm::vec3 newPosition);
        void kill();


};
#endif

