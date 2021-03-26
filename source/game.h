#include "main.h"

#ifndef GAME_H
#define GAME_H

#include "maze.h"
#include "player.h"
#include "entryexit.h"
#include "buttons.h"

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
    int playerHealth;
    int tasksDone;
    int imposterAlive;
    void decreaseHealth();
    int checkContinue();
    void pressButtons();

private:
    Maze maze;
    EntryExit entry;
    EntryExit exit;
    Buttons killImposter;
    float height, width;
};

#endif