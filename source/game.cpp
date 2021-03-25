#include "game.h"
#include "main.h"

Game::Game(int height, int width)
{
    this->maze = Maze(height, width);
    this->height = height;
    this->width = width;
    this->player = Player(0, 0);
}

void Game::draw(glm::mat4 VP)
{
    this->maze.draw(VP);
    this->player.draw(VP);
}

void Game::movePlayer(float x, float y)
{
    this->player.move(x, y);
}