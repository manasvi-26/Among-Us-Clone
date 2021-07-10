#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <vector>
#include "../../Utitlity/shader/shader.h"
#include "../../Utitlity/spriteRenderer/spriteRenderer.h"

// #include "../global.h"

class Button{
    public:
        float width;
        glm::vec3 position;
        int row, col;
        bool buttonType; //0 for red button 1 for green
        unsigned int VAO;

        SpriteRenderer sprite;

        bool check;
        void  move(glm::vec3 position);
        void init(glm::vec3 position, int row , int col, bool Type);
        void render(Shader shader, Texture texture);
        
};

#endif