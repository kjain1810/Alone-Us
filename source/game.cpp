#include "game.h"
#include "main.h"

Game::Game(float height, float width, color_t pbodycol, color_t peyecol, color_t ibodycol, color_t ieyecol)
{
    this->maze = Maze(height, width);
    this->entry = EntryExit(-0.75f, -12.0f);
    this->exit = EntryExit(-0.75f, 11.0f);
    this->killImposter = Buttons(-11.0f, 0.0f);
    this->height = height;
    this->width = width;
    this->player = Player(0, -11.75f, pbodycol, peyecol);
    this->imposter = Player(-11.75f, 4.0f, ibodycol, ieyecol);
    this->playerHealth = 100;
    this->tasksDone = 0;
    this->imposterAlive = 1;
}

void Game::draw(glm::mat4 VP)
{
    this->maze.draw(VP);
    this->entry.draw(VP);
    this->exit.draw(VP);
    this->killImposter.draw(VP);
    this->player.draw(VP);
    if (this->imposterAlive)
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

void Game::decreaseHealth()
{
    this->playerHealth -= 1;
}

int Game::checkContinue()
{
    // Player health!!
    if (this->playerHealth <= 0)
        return 1;
    // Caught by imposter
    bounding_box_t playerbb, imposterbb;
    playerbb.x = this->player.position.x - 0.15f;
    playerbb.y = this->player.position.y - 0.24f;
    playerbb.height = 0.49f;
    playerbb.width = 0.3f;
    imposterbb.x = this->imposter.position.x - 0.15f;
    imposterbb.y = this->imposter.position.y - 0.24f;
    imposterbb.height = 0.49f;
    imposterbb.width = 0.3f;
    if (this->imposterAlive && detect_collision(playerbb, imposterbb))
        return 2;
    // Reached exit
    bounding_box_t exitbb;
    exitbb.x = this->exit.position.x;
    exitbb.y = this->exit.position.y;
    exitbb.width = 1.5f;
    exitbb.height = 1.5f;
    if (this->tasksDone == 2 && detect_collision(playerbb, exitbb))
        return 3;
    return 0;
}

void Game::pressButtons()
{
    bounding_box_t playerbb;
    playerbb.x = this->player.position.x - 0.15f;
    playerbb.y = this->player.position.y - 0.24f;
    playerbb.height = 0.49f;
    playerbb.width = 0.3f;
    bool nearKillButton = false;
    float distX = abs(this->killImposter.position.x - playerbb.x);
    float distY = abs(this->killImposter.position.y - playerbb.y);
    float radius = this->killImposter.radius;
    if (distX > playerbb.width / 2 + radius || distY > playerbb.height / 2 + radius)
        ;
    else
    {
        float cornerdist = (distX - playerbb.width / 2) * (distX - playerbb.width / 2) + (distY - playerbb.height / 2) * (distY - playerbb.height / 2);
        if (distX <= playerbb.width || distY <= playerbb.height || cornerdist <= radius * radius)
            nearKillButton = true;
    }
    if (nearKillButton)
    {
        this->imposterAlive = false;
        this->tasksDone += 1;
    }
}