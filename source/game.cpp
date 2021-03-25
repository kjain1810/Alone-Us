#include "game.h"
#include "main.h"

Game::Game(float height, float width, color_t pbodycol, color_t peyecol, color_t ibodycol, color_t ieyecol)
{
    this->maze = Maze(height, width);
    this->height = height;
    this->width = width;
    this->player = Player(0, 0, pbodycol, peyecol);
    this->imposter = Player(1, 0, ibodycol, ieyecol);
}

void Game::draw(glm::mat4 VP)
{
    // this->maze.draw(VP);
    this->player.draw(VP);
    this->imposter.draw(VP);
}

void Game::movePlayer(float x, float y)
{
    this->player.move(x, y);
}