#include "game.h"
#include "main.h"

Game::Game(float height, float width, color_t pbodycol, color_t peyecol, color_t ibodycol, color_t ieyecol)
{
    this->maze = Maze(height, width);
    this->height = height;
    this->width = width;
    this->player = Player(0, -11.75f, pbodycol, peyecol);
    this->imposter = Player(-11.75f, 4.0f, ibodycol, ieyecol);
}

void Game::draw(glm::mat4 VP)
{
    this->maze.draw(VP);
    this->player.draw(VP);
    this->imposter.draw(VP);
}

bool Game::movePlayer(float x, float y)
{
    bounding_box_t playerbb;
    bounding_box_t wall;
    playerbb.x = this->player.position.x - 0.15f + x;
    playerbb.y = this->player.position.y - 0.24f + y;
    playerbb.height = 0.49f;
    playerbb.width = 0.3f;
    for (int a = 0; a < this->maze.walls.size(); a++)
    {
        wall.x = this->maze.walls[a][0].x;
        wall.y = this->maze.walls[a][0].y;
        wall.height = this->maze.walls[a][1].y - this->maze.walls[a][0].y;
        wall.width = this->maze.walls[a][2].x - this->maze.walls[a][1].x;
        if (detect_collision(playerbb, wall))
            return false;
    }
    this->player.move(x, y);
    return true;
}