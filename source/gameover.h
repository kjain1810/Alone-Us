#include "main.h"

#ifndef GAMEOVER_H
#define GAMEOVER_H

class GameOver
{
public:
    GameOver() {}
    GameOver(float, float);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4, int);

private:
    VAO *object[2];
};

#endif