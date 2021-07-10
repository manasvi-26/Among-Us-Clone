#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <queue>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../Utitlity/shader/shader.h"
#include "../maze/maze.h"
#include "../player/player.h"
#include "../imposter/imposter.h"


#include "../button/button.h"
#include "../GameObjects/GameObjects.h"
#include "../../Utitlity/ResourceManager/ResourceManager.h"

#include "hud.cpp"

#include <iostream>
#include <vector>



enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_LOSE
};

class Game {

    public:

        glm:: mat4 CameraView;

        glm:: vec3 playerPosition;
        glm:: vec3 imposterPosition;
        glm:: vec3 exitPosition;


        glm:: vec3 cameraPosition;
        glm:: vec3 cameraLook;

        ResourceManager manager;
        Hud myHud;

        float start_x, start_y, width;
        int rows,cols;
        float tick;
        GameState state;

        bool gameOver;

        int health ;
        int tasks;
        float timer;
        float start_timer;
        float totalTime;
        void init();
        void input(std::string direction);
        float checkWallCollisions(std::string direction);

        void render();
        void wallCollision();
        void CameraUpdate(float deltaX, float deltaY);
        void update();
        void checkObjectCollsion();
        void CreateTasks(int row ,int col);
        void SpawnPowerups();
        void checkPlayerCollision();
        void Bfs();
        void KillImposter();
        void checkExit();

        glm::vec3 generateCoordinates(int row, int col);
        std::pair<int,int> getNode(float posX, float posY);
        
};

#endif