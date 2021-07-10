#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../texture/texture.h"
#include "../shader/shader.h"


class SpriteRenderer
{
    public:

        Shader shader; 
        unsigned int VAO, EBO;
        void initRenderData(float width);
        
        void DrawSprite(Texture &texture, glm::vec3 position,Shader &shader);
        void DrawSprite(Texture &texture, glm::vec3 position, Shader & shader,float rotation);

   

        
};

#endif