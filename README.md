# Computer Graphics - Assignment 1
## Among Us game in Opengl
In this assignment , using opengl , we were supposed to code a 2d among us single player variant

### GamePlay
- ### Feautures
- You play as a blue crewmate who has the objective to finsih 2 tasks and get out of the maze as soon as possible
- These tasks are orange coloured spaces in the maze and you are required to go to these points to complete
-  Completion of a task is one step closer to you escaping and also rewards you 5 health points
- There is also a red coloured imposter who is chasing after you the whole time (with shortest path algorithm too!!)
- On coming in close vicinity of the imposter (1 maze cell) , he will kill you
- There is a red circular button which you can press by standing on it. This will kill the imposter
- There is a green button which spawns powerups and obstacles.
- The powerups are spinning coins that increase your health by 5 points
- Obstacles are wood boxes that hurt the player if you stand on them. It keeps taking away 2 health points if you stand on it

- You win if you complete 2 tasks and exit from the top right
- You have 120 seconds to escape
- You lose if the imposter catches you , time runs out
- ### Controls
- Player Movement - W(UP)   A(LEFT)   S(DOWN)  D(RIGHT)
- Quit - Esc

#### How to run
- Go into the folder
- Make a build folder - "mkdir build"
- Go in the build folder - "cd build"
- Configure with cmake - "cmake .." in the build foler
- compile , run make in the build folder - "make"
- Run "./Among-Us"




