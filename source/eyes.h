#include "main.h"

#ifndef PLAYERBODY_EYES_H
#define PLAYERBODY_EYES_H

class Eyes
{
public:
    Eyes() {}
    Eyes(float, float, color_t);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4, glm::vec3);

private:
    VAO *object;
};

#endif