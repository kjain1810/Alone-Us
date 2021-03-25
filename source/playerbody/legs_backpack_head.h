#include "main.h"

#ifndef PLAYERBODY_LEGS_H
#define PLAYERBODY_LEGS_H

class Legs
{
public:
    Legs() {}
    Legs(float, float);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4, glm::vec3);

private:
    VAO *object;
};

#endif