#include "hud_text.h"

#include <vector>

HUD_text::HUD_text(float x, float y, color_t bodycol, color_t eyecol)
{
    this->position = glm::vec3(x, y, 0.0f);
    this->rotation = 0.0f;
    this->imposter = Player(x + 2.5, y + 0.5, bodycol, eyecol);
    this->coin = Coin(x + 4, y + 0.25);
    this->boxCoin[0] = Box(x, y, COLOR_RED);
    this->boxCoin[1] = Box(x, y, COLOR_GREEN);
    this->boxImposter[0] = Box(x, y, COLOR_RED);
    this->boxImposter[1] = Box(x, y, COLOR_GREEN);
    this->boxLight[0] = Box(x, y, COLOR_RED);
    this->boxLight[1] = Box(x, y, COLOR_GREEN);
}

void HUD_text::move(float x, float y)
{
    this->position += glm::vec3(x, y, 0.0f);
    this->imposter.position += glm::vec3(x, y, 0.0f);
    this->coin.position += glm::vec3(x, y, 0.0f);
    for (int a = 0; a < 2; a++)
    {
        this->boxCoin[a].position += glm::vec3(x, y, 0.0f);
        this->boxImposter[a].position += glm::vec3(x, y, 0.0f);
        this->boxLight[a].position += glm::vec3(x, y, 0.0f);
    }
}

void HUD_text::draw(glm::mat4 VP, int health, bool imposterTask, bool coinsTask, int lights)
{
    this->object = this->getText(health, imposterTask, coinsTask, lights);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->imposter.draw(VP);
    this->coin.draw(VP, 0.5f);
    this->boxImposter[imposterTask].draw(VP, glm::vec3(3, 0.35, 0), 0.25);
    this->boxCoin[coinsTask].draw(VP, glm::vec3(5, 0.35, 0.0f), 0.25);
    this->boxLight[lights].draw(VP, glm::vec3(7, 0.35, 0.0f), 0.25);
}

VAO *HUD_text::getText(int health, bool imposterTask, bool coinsTask, int lights)
{
    std::vector<glm::vec2> vertices; // vertices of lines

    // HEALTH
    vertices.push_back(glm::vec2(0.1 + 0.2, 0.5));
    vertices.push_back(glm::vec2(0.1 + 0.1, 0.6));
    vertices.push_back(glm::vec2(0.1 + 0.0, 0.5));
    vertices.push_back(glm::vec2(0.1 + 0.4, 0.5));
    vertices.push_back(glm::vec2(0.1 + 0.3, 0.6));
    vertices.push_back(glm::vec2(0.1 + 0.2, 0.5));
    vertices.push_back(glm::vec2(0.1 + 0.0, 0.5));
    vertices.push_back(glm::vec2(0.1 + 0.4, 0.5));
    vertices.push_back(glm::vec2(0.1 + 0.2, 0.3));

    //LIGHT
    vertices.push_back(glm::vec2(6 + 0.00, 0.25 + 0.00));
    vertices.push_back(glm::vec2(6 + 0.00, 0.25 + 0.50));
    vertices.push_back(glm::vec2(6 + 0.10, 0.25 + 0.50));
    vertices.push_back(glm::vec2(6 + 0.10, 0.25 + 0.50));
    vertices.push_back(glm::vec2(6 + 0.00, 0.25 + 0.00));
    vertices.push_back(glm::vec2(6 + 0.10, 0.25 + 0.00));

    vertices.push_back(glm::vec2(6 + 0.00, 0.25 + 0.00));
    vertices.push_back(glm::vec2(6 + 0.00, 0.25 + 0.10));
    vertices.push_back(glm::vec2(6 + 0.30, 0.25 + 0.00));
    vertices.push_back(glm::vec2(6 + 0.00, 0.25 + 0.10));
    vertices.push_back(glm::vec2(6 + 0.30, 0.25 + 0.00));
    vertices.push_back(glm::vec2(6 + 0.30, 0.25 + 0.10));

    // NUMBERS
    std::vector<int> digs;
    while (health)
    {
        digs.push_back(health % 10);
        health /= 10;
    }
    for (int a = 0; a < digs.size() / 2; a++)
        std::swap(digs[a], digs[digs.size() - 1 - a]);
    for (int a = 0; a < digs.size(); a++)
    {
        addNumberEdges(vertices, digs[a], 0.75 + a * 0.3, 0.3, 0.25);
    }
    GLfloat all_vertex_buffer_data[3 * vertices.size()];
    for (int a = 0; a < vertices.size(); a++)
    {
        all_vertex_buffer_data[3 * a] = vertices[a].x;
        all_vertex_buffer_data[3 * a + 1] = vertices[a].y;
        all_vertex_buffer_data[3 * a + 2] = 0.0f;
    }
    return create3DObject(GL_TRIANGLES, vertices.size(), all_vertex_buffer_data, COLOR_WHITE, GL_FILL);
}

void addNumberEdges(std::vector<glm::vec2> &vec, int dig, float x, float y, float scale)
{
    std::vector<glm::vec2> here;
    if (dig == 0)
    {
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.0, 0.1));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));

        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.1, 0.0));
        here.push_back(glm::vec2(0.1, 1.0));
        here.push_back(glm::vec2(0.1, 1.0));
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.0, 1.0));

        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(1.0, 0.9));
        here.push_back(glm::vec2(1.0, 0.9));
        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));

        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 1.0));
    }
    else if (dig == 1)
    {
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(0.9, 1.0));
    }
    else if (dig == 2)
    {
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.0, 0.1));

        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(0.0, 0.55));

        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(1.0, 0.9));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(0.0, 1.0));

        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.1, 0.0));
        here.push_back(glm::vec2(0.1, 0.55));
        here.push_back(glm::vec2(0.1, 0.55));
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.0, 0.55));

        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(0.9, 0.45));
        here.push_back(glm::vec2(0.9, 0.45));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 0.45));
    }
    else if (dig == 3)
    {
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.0, 0.1));

        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(0.0, 0.55));

        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 0.9));
        here.push_back(glm::vec2(1.0, 0.9));
        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.9));

        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(0.9, 1.0));
    }
    else if (dig == 4)
    {
        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.1, 1.0));
        here.push_back(glm::vec2(0.1, 0.4));
        here.push_back(glm::vec2(0.1, 0.4));
        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.4));

        here.push_back(glm::vec2(0.0, 0.4));
        here.push_back(glm::vec2(0.0, 0.5));
        here.push_back(glm::vec2(1.0, 0.5));
        here.push_back(glm::vec2(1.0, 0.5));
        here.push_back(glm::vec2(0.0, 0.4));
        here.push_back(glm::vec2(1.0, 0.4));

        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(0.9, 0.0));
    }
    else if (dig == 5)
    {
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.0, 0.1));

        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(0.0, 0.55));

        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(1.0, 0.9));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(0.0, 1.0));

        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(0.9, 0.55));
        here.push_back(glm::vec2(0.9, 0.55));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.55));

        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.1, 1.0));
        here.push_back(glm::vec2(0.1, 0.45));
        here.push_back(glm::vec2(0.1, 0.45));
        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.45));
    }
    else if (dig == 6)
    {
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.0, 0.1));

        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(0.0, 0.55));

        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(1.0, 0.9));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(0.0, 1.0));

        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(0.9, 0.55));
        here.push_back(glm::vec2(0.9, 0.55));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.55));

        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.1, 1.0));
        here.push_back(glm::vec2(0.1, 0.0));
        here.push_back(glm::vec2(0.1, 0.0));
        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.0));
    }
    else if (dig == 7)
    {
        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(1.0, 0.9));

        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 0.0));
    }
    else if (dig == 8)
    {
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.0, 0.1));

        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(0.0, 0.55));

        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(1.0, 0.9));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(0.0, 1.0));

        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 1.0));

        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.1, 1.0));
        here.push_back(glm::vec2(0.1, 0.0));
        here.push_back(glm::vec2(0.1, 0.0));
        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.0));
    }
    else if (dig == 9)
    {
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(1.0, 0.1));
        here.push_back(glm::vec2(0.0, 0.0));
        here.push_back(glm::vec2(0.0, 0.1));

        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.45));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(1.0, 0.55));
        here.push_back(glm::vec2(0.0, 0.45));
        here.push_back(glm::vec2(0.0, 0.55));

        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(1.0, 0.9));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(1.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.9));
        here.push_back(glm::vec2(0.0, 1.0));

        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(0.9, 0.0));
        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(0.9, 1.0));
        here.push_back(glm::vec2(1.0, 0.0));
        here.push_back(glm::vec2(1.0, 1.0));

        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.1, 1.0));
        here.push_back(glm::vec2(0.1, 0.45));
        here.push_back(glm::vec2(0.1, 0.45));
        here.push_back(glm::vec2(0.0, 1.0));
        here.push_back(glm::vec2(0.0, 0.45));
    }
    for (int a = 0; a < here.size(); a++)
    {
        here[a].x = here[a].x * scale + x;
        here[a].y = here[a].y * scale + y;
        vec.push_back(here[a]);
    }
}