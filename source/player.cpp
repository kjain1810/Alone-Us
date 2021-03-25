#include "player.h"
#include <vector>

Player::Player(float x, float y, color_t bodycol, color_t eyecol)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->body = Mainbody(0.0f, 0.0f, bodycol);
    this->eyes = Eyes(0.0f, 0.0f, eyecol);
    this->head = Head(0.0f, 0.0f, bodycol);
}

void Player::draw(glm::mat4 VP)
{
    this->head.draw(VP, this->position);
    this->body.draw(VP, this->position);
    this->eyes.draw(VP, this->position);
}

void Player::move(float x, float y)
{
    this->position.x += x;
    this->position.y += y;
}