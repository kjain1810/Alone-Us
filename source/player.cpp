#include "player.h"
#include <vector>

Player::Player(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->body = Mainbody(x, y);
    this->eyes = Eyes(x, y);
    this->head = Head(x, y);
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