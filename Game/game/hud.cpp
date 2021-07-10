#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLT_IMPLEMENTATION
#include "gltext.h"

#include <iostream>
#include<vector>


class Hud
{
public:

    
    void text_draw(const char * str1,const char * str2)
    {
        GLTtext *text1 = gltCreateText();
        gltSetText(text1, str1);
        gltBeginDraw();

        gltColor(1.0f, 1.0f, 1.0f, 1.0f);

        gltDrawText2DAligned(text1,
                             (GLfloat)(1200 / 2),
                             (GLfloat)(1000 / 2),
                             3.0f,
                             GLT_CENTER, GLT_CENTER);

        GLTtext *text2 = gltCreateText();
        gltSetText(text2, str2);
        gltColor(1.0f, 0.0f, 0.0f, 1.0f);

        gltDrawText2DAligned(text2,
                             (GLfloat)(1200 / 2),
                             (GLfloat)(600),
                             2.0f,
                             GLT_CENTER, GLT_CENTER);

        gltEndDraw();
    }
    void start()
    {
        const char * str1 = "Welcome!";
        const char * str2 = "Press 'Enter' to Start the Game!";

        text_draw(str1, str2);
    }
    void lose()
    {
        const char * str1 = "Game Over!";
        const char * str2 =  "Press 'Esc' to Quit!";

        text_draw(str1, str2);
    }
    void win()
    {
        const char * str1 = "You Won!";
        const char * str2 =  "Press 'Esc' to Quit!";

        text_draw(str1, str2);

    }
    void activeDrawtext(const char* str, float x, float y )
    {
        GLTtext *text = gltCreateText();
        gltSetText(text, str);
        gltBeginDraw();

        gltColor(0.0f, 1.0f, 1.0f, 1.0f);
        gltDrawText2D(text, x, y, 2.0f);

        gltEndDraw();
    }
    void active(int tasks, int totalTasks, int health, float time)
    {
        char str1[30];
        sprintf(str1,"Tasks Completed : %d/%d", tasks, totalTasks);
        activeDrawtext( str1, 0.0f, 0.0f);

        char str2[30];
        sprintf(str2,"Player Health : %d", health);
        activeDrawtext( str2, 0.0f, 50.0f);

        activeDrawtext("Light : ON", 0.0f, 100.0f);

        char str3[30];
        sprintf(str3,"Timer : %.0fs", time);
        activeDrawtext(str3, 0.0f, 150.0f);
    
    };
};
