#include "main.h"

#ifndef PLAYERBODY_LEGS_H
#define PLAYERBODY_LEGS_H

class Head
{
public:
    Head() {}
    Head(float, float, color_t);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4, glm::vec3);

private:
    VAO *object;
};

#endif