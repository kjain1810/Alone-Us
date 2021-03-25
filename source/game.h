#include "main.h"

#ifndef GAME_H
#define GAME_H

#include "maze.h"
#include "player.h"

class Game
{
public:
    Game() {}
    Game(float height, float width, color_t, color_t, color_t, color_t);
    void draw(glm::mat4);
    bool movePlayer(float, float);
    void moveImposter();
    Player player;
    Player imposter;

private:
    Maze maze;
    float height, width;
};

#endif