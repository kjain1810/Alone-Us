#include "main.h"

#ifndef ENTRYEXIT_H
#define ENTRYEXIT_H

class EntryExit
{
public:
    EntryExit() {}
    EntryExit(float, float);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4);

private:
    VAO *object;
};

#endif