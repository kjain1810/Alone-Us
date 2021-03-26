#include "main.h"

#ifndef COINS_H
#define COINS_H

class Coin
{
public:
    Coin() {}
    Coin(float, float);
    glm::vec3 position;
    float rotation;
    bool notTaken;
    void draw(glm::mat4);

private:
    VAO *object;
};

#endif