#include "maze.h"

void Maze :: init(float x, float y, int rows, int cols , float width){

    this->rows = rows;
    this->cols = cols;

    start_x = x;
    start_y = y;


    unit_length = (float)width/rows;  

    model =  glm::mat4(1.0f);
 
    
    for(int i=0;i<rows;i++){
        vector<Node>arr;
        for(int j = 0;j<cols;j++){

            Node currNode(j, i);
            arr.push_back(currNode);
        }
        grid.push_back(arr);
    }
    

    this->setEdges();
    this->Kruskal();
    this->RenderMaze();
    this->BufferData();
    
}



Node* find_root(Node *node){

    Node* temp = node;
    while(temp->parent != NULL){
        temp= temp->parent;
    }
    return temp;
}

bool merge(Node *node1, Node *node2){

    Node* root1 = find_root(node1);
    Node* root2 = find_root(node2);

    if(root1 == root2)return false;

    if(root1->size >= root2->size){
        root2->parent = root1;
        root1->size += root2->size;
    }
    else{
        root1->parent = root2;
        root2->size += root1->size;
    }

    return true;
}

void Maze :: setEdges(){

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){

            if(i >0){
                edge curr_edge;
                curr_edge.node1 = &(grid[i][j]);
                curr_edge.node2 = &(grid[i - 1][j]);

                edges.push_back(curr_edge);
            }
            if(j >0){
                edge curr_edge;
                curr_edge.node1 = &(grid[i][j]);
                curr_edge.node2 = &(grid[i][j - 1]);

                edges.push_back(curr_edge);
            }
        }
    }
    
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(edges.begin(), edges.end(), rng);
}

void Maze :: Kruskal(){

    for(int i=0;i < edges.size();i++){

        Node* node1 = edges[i].node1;
        Node* node2 = edges[i].node2;

        bool check = merge(node1, node2);
        if(check == true){
            if(node1->grid_y == node2->grid_y){
                node2->East = true;
                node1->West = true;
            }
            else{
                node2->South = true;
                node1->North = true;
            }
        }
    }
}


void Maze :: RenderMaze(){
    
   

    for(int i=0;i<rows;i++){
        for(int j= 0;j<cols;j++){

            

            Node* node = &grid[i][j];

            float topLeft[] = {
                start_x + unit_length * node->grid_x,
                start_y - unit_length * node->grid_y,
                0.0f
            };
            float topRight[] = {
                start_x + unit_length * node->grid_x + unit_length,
                start_y - unit_length * node->grid_y,
                0.0f
            };
            float bottomLeft[] = {
                start_x + unit_length * node->grid_x,
                start_y - unit_length * node->grid_y - unit_length,
                0.0f
            };
            float bottomRight[] = {
                start_x + unit_length * node->grid_x + unit_length,
                start_y - unit_length * node->grid_y - unit_length,
                0.0f
            };

            if(node->North == false){
                for(auto f : topLeft)vertices.push_back(f);
                for(auto f : topRight)vertices.push_back(f);
            }

            if(node->West == false){
                for(auto f : topLeft)vertices.push_back(f);
                for(auto f : bottomLeft)vertices.push_back(f);
            }

            if(node->East == false){
                for(auto f : topRight)vertices.push_back(f);
                for(auto f : bottomRight)vertices.push_back(f);
            }

            if(node->South == false){
                for(auto f : bottomLeft)vertices.push_back(f);
                for(auto f : bottomRight)vertices.push_back(f);
            }
        }
    }

    // for(int i=0;i<vertices.size();i++){
    //     if(i%3 == 0)cout << endl;
    //     cout << vertices[i] << " ";
    // }

} 


void Maze :: BufferData()
{
    
    float vert[vertices.size()];
    for(int i=0;i<vertices.size();i++)vert[i]= vertices[i];

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert),vert, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

    this->VAO = VAO;
}

void Maze :: drawMaze(Shader myShader)
{
    
    glBindVertexArray(VAO); 
    myShader.use();
    myShader.setMatrix4("model",this->model);
    int len = vertices.size()/3;
    glDrawArrays(GL_LINES, 0, len);
}


Node ::  Node(int grid_x, int grid_y){

 
    this->grid_x = grid_x;
    this->grid_y = grid_y;

    North = false;
    West = false;
    East = false;
    South = false;
    
    parent = NULL;
    this->size = 1;
    
}

