
#include "game.h"

Maze *myMaze;
Player *myPlayer;
Imposter *myImposter;

vector<Objects *> myGameObjects;

Button *GreenButton;
Button *RedButton;


void Game ::init()
{

    //Set State:

    this->state = GAME_MENU;
    this->tasks = 0;
    this->health = 5;

    //Load Shaders:

    manager.LoadShader("../source/Shader/maze/mazeVertex.shader", "../source/Shader/maze/mazeFragment.shader", "mazeShader");
    manager.LoadShader("../source/Shader/player/playerVertex.shader", "../source/Shader/player/playerFragment.shader", "spriteShader");

    //Load Textures:

    manager.LoadTexture("../source/Images/imp3.png", "imposterTexture", true);
    manager.LoadTexture("../source/Images/player.png", "playerTexture", true);
    manager.LoadTexture("../source/Images/wood.jpg", "obstacleTexture", false);
    manager.LoadTexture("../source/Images/1-up-powerup.png", "powerupTexture", true);
    manager.LoadTexture("../source/Images/red.jpg", "redTexture", false);
    manager.LoadTexture("../source/Images/green.jpg", "greenTexture", false);
    manager.LoadTexture("../source/Images/or.jpg", "taskTexture", false);
    

    //Configuration:

    start_x = -4;
    start_y = 4;
    rows = 20;
    cols = 20;
    width = abs(start_x * 2);
    gameOver = false;

    cameraPosition = glm::vec3(-3.1f, -3.1f, 0.5f);
    cameraLook = glm::vec3(-3.1f, -3.1f, 0.0f);

    playerPosition = generateCoordinates(19, 0);
    imposterPosition = generateCoordinates(3, 18);

    //Init Objects:

    myMaze = new Maze();
    myMaze->init(start_x, start_y, rows, cols, width);

    myPlayer = new Player();
    myPlayer->init(playerPosition);

    myImposter = new Imposter();
    myImposter->init(imposterPosition);

    CameraView = glm::lookAt(cameraPosition, cameraLook, glm::vec3(0.0f, 1.0f, 0.0f));

    //Tasks:
    CreateTasks(rows - 2, 5);
    CreateTasks(rows - 12, 10);


    //Buttons:
    GreenButton = new Button();
    GreenButton->init(generateCoordinates(rows - 5, 5), rows - 5, 5, 0);

    RedButton = new Button();
    RedButton->init(generateCoordinates(rows - 10, 10), rows - 10, 10, 0);

    this->totalTime = 120;

   
    
    
}
void Game ::CreateTasks(int row, int col)
{
    float unit_length = (float)width / rows;
    float half = (float)unit_length / 2;
    Objects *task;
    task = new Objects();

    glm::vec3 position = generateCoordinates(row, col);

    task->init(position, row, col, 0);
    myGameObjects.push_back(task);
}

/***************************************************************************************************************************************/

float Game ::checkWallCollisions(std::string direction)
{

    float stdDelta = 0.01;
    myPlayer->getHitBox();
    float delta = stdDelta;

    for (int i = 0; i < myMaze->vertices.size(); i += 6)
    {

        float wallX1 = myMaze->vertices[i];
        float wallX2 = myMaze->vertices[i + 3];
        float wallY1 = myMaze->vertices[i + 1];
        float wallY2 = myMaze->vertices[i + 4];

        if (wallX1 > wallX2)
            swap(wallX1, wallX2);
        if (wallY1 > wallY2)
            swap(wallY1, wallY2);

        float extra = 0.0000005;
        if (direction == "Up")
        {

            bool cond1 = wallX2 < myPlayer->myHitBox.topLeft.first;
            bool cond2 = wallX1 > myPlayer->myHitBox.topRight.first;

            if (cond1 || cond2)
                continue;
            float y = myPlayer->myHitBox.topLeft.second;

            delta = min(delta, abs(y - wallY1) - extra);
        }

        if (direction == "Down")
        {
            bool cond1 = wallX2 < myPlayer->myHitBox.bottomLeft.first;
            bool cond2 = wallX1 > myPlayer->myHitBox.bottomRight.first;

            if (cond1 || cond2)
                continue;
            float y = myPlayer->myHitBox.bottomLeft.second;

            delta = min(delta, abs(y - wallY2) - extra);
        }
        if (direction == "Left")
        {

            bool cond1 = wallY2 < myPlayer->myHitBox.bottomLeft.second;
            bool cond2 = wallY1 > myPlayer->myHitBox.topLeft.second;

            if (cond1 || cond2)
                continue;
            float x = myPlayer->myHitBox.topLeft.first;

            delta = min(delta, abs(x - wallX2) - extra);
        }
        if (direction == "Right")
        {

            bool cond1 = wallY2 < myPlayer->myHitBox.bottomRight.second;
            bool cond2 = wallY1 > myPlayer->myHitBox.topRight.second;

            if (cond1 || cond2)
                continue;
            float x = myPlayer->myHitBox.topRight.first;

            delta = min(delta, abs(x - wallX1) - extra);
        }
    }

    return delta;
}

void Game ::CameraUpdate(float deltaX, float deltaY)
{
    cameraPosition += glm::vec3(deltaX, deltaY, 0.0f);
    cameraLook += glm::vec3(deltaX, deltaY, 0.0f);
}

void Game ::input(std::string direction)
{

    float delta = checkWallCollisions(direction);

    // cout << delta << endl;
    if (direction == "Up")
    {
        myPlayer->move(0.0f, delta);
        CameraUpdate(0.0f, delta);
    }
    if (direction == "Left")
    {
        myPlayer->move(-delta, 0.0f);
        CameraUpdate(-delta, 0.0f);
    }
    if (direction == "Right")
    {
        myPlayer->move(delta, 0.0f);
        CameraUpdate(delta, 0.0f);
    }
    if (direction == "Down")
    {
        myPlayer->move(0.0f, -delta);
        CameraUpdate(0.0f, -delta);
    }
}

/***************************************************************************************************************************************/

void Game ::checkObjectCollsion()
{
    pair<int, int> node = getNode(myPlayer->position.x, myPlayer->position.y);

    for (auto object : myGameObjects)
    {
        bool cond1 = (object->row == node.first);
        bool cond2 = (object->col == node.second);
        if (cond1 && cond2)
        {
            bool cond = (object->check == false); 
            if(object->type == 0 && cond ){
                this->tasks+=1;
                this->health += 10;
            }
            if(object->type == 1 && cond){
                this->health += 5;
            }
            if(object->type == 2 && cond){
                this->health -= 2;
            }

            object->check = true;
        }
    }

    if ((GreenButton->row == node.first) && (GreenButton->col == node.second))
    {
        GreenButton->move(glm::vec3(-30, -30, 0.0f));
        SpawnPowerups();
        GreenButton->check = true;
    }

    if ((RedButton->row == node.first) && (RedButton->col == node.second))
    {
        KillImposter();
        RedButton->check = true;
        RedButton->move(glm::vec3(-30, -30, 0.0f));
    }
}

void Game ::KillImposter()
{
    myImposter->kill();
}

void Game ::SpawnPowerups()
{

    srand(time(0));
    for (int i = 0; i < 15; i++)
    {
        int row = (rand() % 15 + 2);
        int col = (rand() % 15 + 2);
        // cout << row << " " << col << endl;

        Objects *object;
        object = new Objects();
        if (i < 8)
            object->init(generateCoordinates(row, col), row, col, 1);
        else
            object->init(generateCoordinates(row, col), row, col, 2);

        myGameObjects.push_back(object);
    }
}

std::pair<int, int> Game ::getNode(float posX, float posY)
{
    float unit_length = (float)width / rows;
    float half = (float)unit_length / 2;

    posY = abs(posY - (float)width / 2);
    posX = (posX + float(width) / 2);

    int col = posX / unit_length;
    int row = posY / unit_length;

    return make_pair(row, col);
}

glm::vec3 Game ::generateCoordinates(int row, int col)
{
    float unit_length = (float)width / rows;
    float half = (float)unit_length / 2;

    float x = start_x + unit_length * col + half;
    float y = start_y - unit_length * row - half;

    return glm::vec3(x, y, 0.0f);
}

bool check(pair<int, int> node1, pair<int, int> node2)
{
    bool cond1 = (node1.first == node2.first);
    bool cond2 = (node1.second == node2.second);

    return (cond1 && cond2);
}

void Game ::Bfs()
{
    pair<int, int> nodeImposter = getNode(myImposter->position.x, myImposter->position.y);
    pair<int, int> nodePlayer = getNode(myPlayer->position.x, myPlayer->position.y);

    std ::queue<pair<int, int>> q;
    vector<vector<int>> vis(rows, vector<int>(cols, 0));

    q.push(nodePlayer);
    vis[nodePlayer.first][nodePlayer.second] = 1;


    pair<int, int> next;

    while (!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;

        if (myMaze->grid[row][col].North == true)
        {
            if (!vis[row - 1][col])
            {
                pair<int, int> curr = make_pair(row - 1, col);
                if (check(nodeImposter, curr))
                    next = q.front();
                q.push(make_pair(row - 1, col));
                vis[row - 1][col] = 1;
            }
        }
        if (myMaze->grid[row][col].South == true)
        {
            if (!vis[row + 1][col])
            {
                pair<int, int> curr = make_pair(row + 1, col);
                if (check(nodeImposter, curr))
                    next = q.front();
                q.push(make_pair(row + 1, col));
                vis[row + 1][col] = 1;
            }
        }
        if (myMaze->grid[row][col].East == true)
        {
            if (!vis[row][col + 1])
            {
                pair<int, int> curr = make_pair(row, col + 1);
                if (check(nodeImposter, curr))
                    next = q.front();
                q.push(make_pair(row, col + 1));
                vis[row][col + 1] = 1;
            }
        }
        if (myMaze->grid[row][col].West == true)
        {
            if (!vis[row][col - 1])
            {
                pair<int, int> curr = make_pair(row, col - 1);
                if (check(nodeImposter, curr))
                    next = q.front();
                q.push(make_pair(row, col - 1));
                vis[row][col - 1] = 1;
            }
        }

        q.pop();
    }

    myImposter->move(generateCoordinates(next.first, next.second));
}

void Game ::checkPlayerCollision()
{
    pair<int, int> nodeImposter = getNode(myImposter->position.x, myImposter->position.y);
    pair<int, int> nodePlayer = getNode(myPlayer->position.x, myPlayer->position.y);

    if (check(nodeImposter, nodePlayer))
        this->state = GAME_LOSE;
}

void Game :: checkExit()
{
    pair<int,int> node = getNode(myPlayer->position.x, myPlayer->position.y);
    bool cond1 = (node.first == 0);
    bool cond2 =  (node.second == cols-1);
    bool cond3 = (this->tasks == 2);
    bool cond4 = (myImposter->dead == true);
    if(cond1 && cond2 && cond3 && cond4){
        this->state = GAME_WIN;
    }
}

void Game ::update()
{

    if ((glfwGetTime() - tick) > 1)
    {
        tick = glfwGetTime();
        if(myImposter->dead == false)Bfs();
    }
    this->timer = round(glfwGetTime() - start_timer);
    checkObjectCollsion();
    checkPlayerCollision();
    
    if(this->timer > 120)this->state = GAME_LOSE;
    checkExit();
}

/***************************************************************************************************************************************/

void Game ::render()
{

    gltInit();

    if (this->state == GAME_MENU)
    {
        myHud.start();
    }
    if (this->state == GAME_ACTIVE)
    {

        CameraView = glm::lookAt(cameraPosition, cameraLook, glm::vec3(0.0f, 1.0f, 0.0f));
        // CameraView = glm::mat4(1.0f);

        glm::mat4 Projection = glm::mat4(1.0f);
        // glm::mat4 Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 0.0f);

        Shader mazeShader = manager.GetShader("mazeShader");
        Shader spriteShader = manager.GetShader("spriteShader");

        Texture playerTexture = manager.GetTexture("playerTexture");
        Texture imposterTexture = manager.GetTexture("imposterTexture");
        Texture taskTexture = manager.GetTexture("taskTexture");
        Texture powerupTexture = manager.GetTexture("powerupTexture");
        Texture obstacleTexture = manager.GetTexture("obstacleTexture");
        Texture greenTexture = manager.GetTexture("greenTexture");
        Texture redTexture = manager.GetTexture("redTexture");

        mazeShader.setMatrix4("view", CameraView);
        mazeShader.setMatrix4("projection", Projection);

        spriteShader.setMatrix4("view", CameraView);
        spriteShader.setMatrix4("projection", Projection);

        myMaze->drawMaze(mazeShader);

        for (auto object : myGameObjects)
        {
            if (object->check == false)
            {
                if (object->type == 0)
                    object->render(spriteShader, taskTexture);
                if (object->type == 1)
                {
                    object->render(spriteShader, powerupTexture);
                }
                if (object->type == 2)
                    object->render(spriteShader, obstacleTexture);
            }
        }

        GreenButton->render(spriteShader, greenTexture);
        RedButton->render(spriteShader, redTexture);

        myPlayer->render(spriteShader, playerTexture);

        if (myImposter->dead == false)
            myImposter->render(spriteShader, imposterTexture);

        // Exit->render(spriteShader,manager.GetTexture("exitTexture"));

        myHud.active(this->tasks, 2, this->health, (this->totalTime - this->timer));
        
    }
    if(this->state == GAME_LOSE){
        myHud.lose();
    }
    if(this->state == GAME_WIN){
        myHud.win();
    }


    
}
