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

void Game::moveImposter()
{
    float x = this->player.position.x - this->imposter.position.x;
    float y = this->player.position.y - this->imposter.position.y;
    float x_hat = x / sqrt(x * x + y * y);
    float y_hat = y / sqrt(x * x + y * y);
    x_hat *= move_x;
    y_hat *= move_y;
    bounding_box_t imposterbb;
    bounding_box_t wall;
    imposterbb.x = this->imposter.position.x - 0.15f + x_hat;
    imposterbb.y = this->imposter.position.y - 0.24f;
    imposterbb.height = 0.49f;
    imposterbb.width = 0.3f;
    bool flag_x = true;
    for (int a = 0; a < this->maze.walls.size(); a++)
    {
        wall.x = this->maze.walls[a][0].x;
        wall.y = this->maze.walls[a][0].y;
        wall.height = this->maze.walls[a][1].y - this->maze.walls[a][0].y;
        wall.width = this->maze.walls[a][2].x - this->maze.walls[a][1].x;
        if (detect_collision(imposterbb, wall))
            flag_x = false;
    }
    if (flag_x)
        this->imposter.move(x_hat, 0);
    imposterbb.x = this->imposter.position.x - 0.15f;
    imposterbb.y = this->imposter.position.y - 0.24f + y_hat;
    bool flag_y = true;
    for (int a = 0; a < this->maze.walls.size(); a++)
    {
        wall.x = this->maze.walls[a][0].x;
        wall.y = this->maze.walls[a][0].y;
        wall.height = this->maze.walls[a][1].y - this->maze.walls[a][0].y;
        wall.width = this->maze.walls[a][2].x - this->maze.walls[a][1].x;
        if (detect_collision(imposterbb, wall))
            flag_y = false;
    }
    if (flag_y)
        this->imposter.move(0, y_hat);
}