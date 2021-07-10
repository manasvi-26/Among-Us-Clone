#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLT_IMPLEMENTATION
#include "gltext.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window);

const unsigned int SCREEN_WIDTH = 1200;
const unsigned int SCREEN_HEIGHT =1000;

#include "Game/game/game.h"

#define GLT_IMPLEMENTATION
#include "gltext.h"

Game myGame;

int main()
{
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TEST", nullptr, nullptr);
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    myGame.init();

    while (!glfwWindowShouldClose(window))
    {
        
        glfwPollEvents();
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myGame.update();
        myGame.render();

        glfwSwapBuffers(window);
    }

}


void processInput(GLFWwindow * window){

    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
    if(glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS && myGame.state == GAME_MENU )
    {
        myGame.state = GAME_ACTIVE;
        myGame.start_timer = glfwGetTime();
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        myGame.input("Left");
    }
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        myGame.input("Up");
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        myGame.input("Down");
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        myGame.input("Right");
    }

}



void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

