#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player() {}
    Player(int, int);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4);
    void move(float, float);

private:
    VAO *object;
};

#endif