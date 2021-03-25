#ifndef MAZE_H
#define MAHE_H

#include "main.h"

class Maze
{
public:
    Maze() {}
    Maze(float, float);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4);

private:
    int height, width;
    VAO *object;
};

#endif