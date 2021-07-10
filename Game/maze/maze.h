#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <random>
#include <algorithm>
#include <vector>
#include "../../Utitlity/shader/shader.h"

using namespace std;

class Node{
    
    public :

        int unit_length;
        int grid_x, grid_y;
        int size;
        Node* parent;

        bool North, West, East, South;

        Node(int grid_x, int grid_y);
        
};

struct edge{
    Node* node1;
    Node* node2;
};


class Maze {

    public :
    
        int rows,cols;
        float start_x,start_y;
        float unit_length;

        unsigned int VAO;


        glm::mat4 model;

        // Shader myShader;

        vector<vector<Node>>grid;
        vector<edge> edges;

        vector<float> vertices;

        void init(float x, float y, int row, int col, float width);

        
        void setEdges();
        void Kruskal(); 
        void BufferData();
        void RenderMaze();
        void drawMaze(Shader myShader);
};



#endif