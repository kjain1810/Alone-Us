#include "main.h"

#ifndef HUD_TEXT_H
#define HUD_TEXT_H

#include "player.h"
#include "coins.h"
#include "boxes.h"

class HUD_text
{
public:
    HUD_text() {}
    HUD_text(float, float, color_t, color_t);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4, int, bool, bool, int);
    void move(float, float);
    Player imposter;
    Coin coin;
    Box boxImposter[2];
    Box boxCoin[2];
    Box boxLight[2];

private:
    VAO *object;
    VAO *getText(int, bool, bool, int);
};

#endif