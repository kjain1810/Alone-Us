#ifndef MAZE_H
#define MAHE_H

#include "main.h"
#include <vector>

class Maze
{
public:
    Maze() {}
    Maze(float, float);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4);
    std::vector<std::vector<glm::vec3>> walls;

private:
    int height, width;
    VAO *object;
    void createSquare(glm::vec3, glm::vec3, glm::vec3, glm::vec3, std::vector<glm::vec3> &);
};

#endif