#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H

#include "eyes.h"
#include "head.h"
#include "mainbody.h"

class Player
{
public:
    Player() {}
    Player(float, float);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4);
    void move(float, float);

private:
    Eyes eyes;
    Mainbody body;
    Head head;
};

#endif