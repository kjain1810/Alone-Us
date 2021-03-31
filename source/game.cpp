#include "game.h"
#include "main.h"

#include <random>
#include <time.h>

Game::Game(float height, float width, color_t pbodycol, color_t peyecol, color_t ibodycol, color_t ieyecol)
{
    srand(time(NULL));
    this->maze = Maze(height, width);
    this->entry = EntryExit(-0.75f, -12.0f);
    this->exit = EntryExit(-0.75f, 11.0f);
    this->killImposter = this->getButton(-12.0f, -4.0f);
    this->powerUps = this->getButton(4.0f, -4.0f);
    this->height = height;
    this->width = width;
    this->player = Player(0, -11.75f, pbodycol, peyecol);
    this->imposter = getImposter(-4.0f, -4.0f, ibodycol, ieyecol);
    this->playerHealth = 100;
    this->tasksDone = 0;
    this->imposterAlive = true;
    this->powerUpsActive = false;
    this->lightsOn = 1;
    int idx = 0;
    for (int a = -12; a <= 4; a += 8)
    {
        for (int b = -12; b <= 4; b += 8)
        {
            float xdiff = ((float)(rand() % 8000)) / 1000.0f;
            float ydiff = ((float)(rand() % 8000)) / 1000.0f;
            this->coins[idx] = Coin((float)a + xdiff, (float)b + ydiff);
            xdiff = ((float)(rand() % 8000)) / 1000.0f;
            ydiff = ((float)(rand() % 8000)) / 1000.0f;
            this->obstacle[idx++] = Obstacle((float)a + xdiff, (float)b + ydiff);
        }
    }
    this->numPowerups = idx;
    this->hud = HUD(-4.0f, -9.0f, ibodycol, ieyecol);
}

void Game::draw(glm::mat4 VP)
{
    Light.stat = this->lightsOn;
    Light.loc = &this->player.position[0];
    glUniform1i(Light.StatusID, this->lightsOn);
    this->maze.draw(VP);
    this->entry.draw(VP);
    this->exit.draw(VP);
    this->killImposter.draw(VP);
    this->powerUps.draw(VP);
    if (this->powerUpsActive)
        for (int a = 0; a < 9; a++)
        {
            if (this->coins[a].notTaken)
                this->coins[a].draw(VP, 1.0f);
            this->obstacle[a].draw(VP);
        }
    this->player.draw(VP);
    if (this->imposterAlive)
        this->imposter.draw(VP);
    glUniform1i(Light.StatusID, 1);
    this->hud.draw(VP, this->playerHealth, !this->imposterAlive, this->powerUpsActive, this->lightsOn);
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
    if (this->powerUpsActive)
        for (int a = 0; a < this->numPowerups; a++)
        {
            wall.x = this->obstacle[a].position.x;
            wall.y = this->obstacle[a].position.y;
            wall.height = 1;
            wall.width = 1;
            if (detect_collision(playerbb, wall))
            {
                this->playerHealth -= 1;
                return false;
            }
        }
    if (this->powerUpsActive)
        for (int a = 0; a < this->numPowerups; a++)
        {
            if (!this->coins[a].notTaken)
                continue;
            wall.x = this->coins[a].position.x;
            wall.y = this->coins[a].position.y;
            wall.height = 1;
            wall.width = 1;
            if (detect_collision(playerbb, wall))
            {
                this->coins[a].notTaken = false;
                this->playerHealth += 5;
            }
        }
    this->player.move(x, y);
    this->hud.move(x, y);
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
    if (this->powerUpsActive)
        for (int a = 0; a < this->numPowerups; a++)
        {
            wall.x = this->obstacle[a].position.x;
            wall.y = this->obstacle[a].position.y;
            wall.height = 1;
            wall.width = 1;
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
    if (this->powerUpsActive)
        for (int a = 0; a < this->numPowerups; a++)
        {
            wall.x = this->obstacle[a].position.x;
            wall.y = this->obstacle[a].position.y;
            wall.height = 1;
            wall.width = 1;
            if (detect_collision(imposterbb, wall))
                flag_x = false;
        }
    if (flag_y)
        this->imposter.move(0, y_hat);
}

void Game::decreaseHealth()
{
    if (this->lightsOn)
        this->playerHealth -= 1;
    else
        this->playerHealth += 1;
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
    if (this->tasksDone == 2 && check_inside(playerbb, exitbb))
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
    if (this->imposterAlive)
    {
        bool nearKillButton = circleRectIntersect(playerbb, this->killImposter.radius, this->killImposter.position);
        if (nearKillButton)
        {
            this->imposterAlive = false;
            this->tasksDone += 1;
        }
    }
    if (!this->powerUpsActive)
    {
        bool nearPowerupButton = circleRectIntersect(playerbb, this->powerUps.radius, this->powerUps.position);
        if (nearPowerupButton)
        {
            this->powerUpsActive = true;
            this->tasksDone += 1;
        }
    }
}

void Game::switchLights()
{
    this->lightsOn = (1 - this->lightsOn);
}

Buttons Game::getButton(float offsetx, float offsety)
{
    float x = ((float)(rand() % 8000)) / 1000.0 + offsetx;
    float y = ((float)(rand() % 16000)) / 1000.0 + offsety;
    bool correct = false;
    bounding_box_t wall;
    while (!correct)
    {
        correct = true;
        for (int a = 0; a < this->maze.walls.size(); a++)
        {
            wall.x = this->maze.walls[a][0].x;
            wall.y = this->maze.walls[a][0].y;
            wall.height = this->maze.walls[a][1].y - this->maze.walls[a][0].y;
            wall.width = this->maze.walls[a][2].x - this->maze.walls[a][1].x;
            if (circleRectIntersect(wall, 0.25f, glm::vec3(x, y, 0.0)))
            {
                correct = false;
                x = ((float)(rand() % 8000)) / 1000.0 + offsetx;
                y = ((float)(rand() % 16000)) / 1000.0 + offsety;
                break;
            }
        }
    }
    return Buttons(x, y);
}

Player Game::getImposter(float offsetx, float offsety, color_t bodycolor, color_t eyecolor)
{
    float x = ((float)(rand() % 8000)) / 1000.0 + offsetx;
    float y = ((float)(rand() % 8000)) / 1000.0 + offsety;
    bool correct = false;
    bounding_box_t wall, imposter;
    imposter.height = 0.49f;
    imposter.width = 0.3f;
    while (!correct)
    {
        correct = true;
        imposter.x = x;
        imposter.y = y;
        for (int a = 0; a < this->maze.walls.size(); a++)
        {
            wall.x = this->maze.walls[a][0].x;
            wall.y = this->maze.walls[a][0].y;
            wall.height = this->maze.walls[a][1].y - this->maze.walls[a][0].y;
            wall.width = this->maze.walls[a][2].x - this->maze.walls[a][1].x;
            if (detect_collision(wall, imposter))
            {
                correct = false;
                x = ((float)(rand() % 8000)) / 1000.0 + offsetx;
                y = ((float)(rand() % 8000)) / 1000.0 + offsety;
                break;
            }
        }
    }
    return Player(x, y, bodycolor, eyecolor);
}