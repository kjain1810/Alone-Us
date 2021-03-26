#include "main.h"

#ifndef BUTTONS_H
#define BUTTONS_H

class Buttons
{
public:
    Buttons() {}
    Buttons(float, float);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4);

private:
    VAO *object;
};

#endif