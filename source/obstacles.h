#include "main.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{
public:
    Obstacle() {}
    Obstacle(float, float);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4);

private:
    VAO *object;
};

#endif