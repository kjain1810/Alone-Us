#include "main.h"

#ifndef GAME_H
#define GAME_H

#include "maze.h"
#include "player.h"

class Game
{
public:
    Game() {}
    Game(float height, float width);
    void draw(glm::mat4);
    void movePlayer(float, float);
    Player player;

private:
    Maze maze;
    float height, width;
};

#endif