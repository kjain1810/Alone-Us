#include "main.h"

#ifndef HUD_H
#define HUD_H

#include "hud_text.h"

class HUD
{
public:
    HUD() {}
    HUD(float, float, color_t, color_t);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4, int, bool, bool, int);
    void move(float, float);

private:
    VAO *object;
    HUD_text text;
};

#endif