#include "main.h"

#ifndef GAME_H
#define GAME_H

#include "maze.h"
#include "player.h"

class Game
{
public:
    Game() {}
    Game(int height, int width);
    void draw(glm::mat4);
    void movePlayer(float, float);
    Player player;

private:
    Maze maze;
    int height, width;
};

#endif