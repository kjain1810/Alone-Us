#include "main.h"

#ifndef GAME_H
#define GAME_H

#include "maze.h"
#include "player.h"
#include "entryexit.h"
#include "buttons.h"
#include "coins.h"
#include "obstacles.h"

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
    bool imposterAlive;
    bool powerUpsActive;
    void decreaseHealth();
    int checkContinue();
    void pressButtons();
    int numPowerups;
    int lightsOn;
    void switchLights();
    Buttons getButton(float, float);
    Player getImposter(float, float, color_t, color_t);

private:
    Maze maze;
    EntryExit entry;
    EntryExit exit;
    Buttons killImposter;
    Buttons powerUps;
    Coin coins[10];
    Obstacle obstacle[10];
    float height, width;
};

#endif