#include "main.h"

#ifndef BOXES_H
#define BOXES_H

class Box
{
public:
    Box() {}
    Box(float, float, color_t);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4, glm::vec3, float scale);

private:
    VAO *object;
};

#endif