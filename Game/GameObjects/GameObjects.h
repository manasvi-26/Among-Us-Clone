#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <vector>
#include "../../Utitlity/shader/shader.h"
#include "../../Utitlity/spriteRenderer/spriteRenderer.h"

// #include "../global.h"

class Objects{
    public:
        float width;
        glm::vec3 position;
        int row, col;
        int type; //0 for task, 1 for powerup 2 for obstacle
        unsigned int VAO;

        SpriteRenderer sprite;

        bool check;
        void init(glm::vec3 position, int row , int col,int type);
        void render(Shader shader, Texture texture);

};

#endif