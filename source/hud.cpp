#include "hud.h"

HUD::HUD(float x, float y, color_t bodycol, color_t eyecol)
{
    this->position = glm::vec3(x, y, 0.0f);
    this->rotation = 0.0f;
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f, // background begin
        0.0f, 1.0f, 0.0f,
        8.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        8.0f, 0.0f, 0.0f,
        8.0f, 1.0f, 0.0f, // background end
    };
    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, COLOR_HUD, GL_FILL);
    this->text = HUD_text(x, y, bodycol, eyecol);
}

void HUD::move(float x, float y)
{
    this->position += glm::vec3(x, y, 0.0f);
    this->text.move(x, y);
}

void HUD::draw(glm::mat4 VP, int health, bool imposterTask, bool coinsTask, int lights)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->text.draw(VP, health, imposterTask, coinsTask, lights);
}