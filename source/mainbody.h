#include "main.h"

#ifndef PLAYERBODY_Mainbody_H
#define PLAYERBODY_Mainbody_H

class Mainbody
{
public:
    Mainbody() {}
    Mainbody(float, float, color_t);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4, glm::vec3);

private:
    VAO *object;
};

#endif