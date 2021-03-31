#include "gameover.h"

#include <vector>

GameOver::GameOver(float x, float y)
{
    this->position = glm::vec3(x, y, 0.0f);
    this->rotation = 0.0f;

    std::vector<glm::vec2> textYouLost, textYouWin;
    {
        // Y
        textYouLost.push_back(glm::vec2(-3, 2));
        textYouLost.push_back(glm::vec2(-4, 3));
        textYouLost.push_back(glm::vec2(-3.8, 3.2));
        textYouLost.push_back(glm::vec2(-3.8, 3.2));
        textYouLost.push_back(glm::vec2(-3, 2));
        textYouLost.push_back(glm::vec2(-2.8, 2.2));

        textYouLost.push_back(glm::vec2(-3, 2));
        textYouLost.push_back(glm::vec2(-2, 3));
        textYouLost.push_back(glm::vec2(-2.2, 3.2));
        textYouLost.push_back(glm::vec2(-2.2, 3.2));
        textYouLost.push_back(glm::vec2(-3, 2));
        textYouLost.push_back(glm::vec2(-3.2, 2.2));

        textYouLost.push_back(glm::vec2(-3.15, 2.2));
        textYouLost.push_back(glm::vec2(-2.85, 2.2));
        textYouLost.push_back(glm::vec2(-2.85, 0.2));
        textYouLost.push_back(glm::vec2(-2.85, 0.2));
        textYouLost.push_back(glm::vec2(-3.15, 2.2));
        textYouLost.push_back(glm::vec2(-3.15, 0.2));

        // O
        textYouLost.push_back(glm::vec2(-1.8, 0.2));
        textYouLost.push_back(glm::vec2(-1.5, 0.2));
        textYouLost.push_back(glm::vec2(-1.5, 3.2));
        textYouLost.push_back(glm::vec2(-1.5, 3.2));
        textYouLost.push_back(glm::vec2(-1.8, 0.2));
        textYouLost.push_back(glm::vec2(-1.8, 3.2));

        textYouLost.push_back(glm::vec2(-0.3, 0.2));
        textYouLost.push_back(glm::vec2(-0.6, 0.2));
        textYouLost.push_back(glm::vec2(-0.6, 3.2));
        textYouLost.push_back(glm::vec2(-0.6, 3.2));
        textYouLost.push_back(glm::vec2(-0.3, 0.2));
        textYouLost.push_back(glm::vec2(-0.3, 3.2));

        textYouLost.push_back(glm::vec2(-1.8, 3.2));
        textYouLost.push_back(glm::vec2(-0.6, 3.2));
        textYouLost.push_back(glm::vec2(-0.6, 2.9));
        textYouLost.push_back(glm::vec2(-0.6, 2.9));
        textYouLost.push_back(glm::vec2(-1.8, 3.2));
        textYouLost.push_back(glm::vec2(-1.8, 2.9));

        textYouLost.push_back(glm::vec2(-1.8, 0.2));
        textYouLost.push_back(glm::vec2(-0.6, 0.2));
        textYouLost.push_back(glm::vec2(-0.6, 0.5));
        textYouLost.push_back(glm::vec2(-0.6, 0.5));
        textYouLost.push_back(glm::vec2(-1.8, 0.2));
        textYouLost.push_back(glm::vec2(-1.8, 0.5));

        // U
        textYouLost.push_back(glm::vec2(0.0, 0.2));
        textYouLost.push_back(glm::vec2(0.3, 0.2));
        textYouLost.push_back(glm::vec2(0.3, 3.2));
        textYouLost.push_back(glm::vec2(0.3, 3.2));
        textYouLost.push_back(glm::vec2(0.0, 0.2));
        textYouLost.push_back(glm::vec2(0.0, 3.2));

        textYouLost.push_back(glm::vec2(1.5, 0.2));
        textYouLost.push_back(glm::vec2(1.2, 0.2));
        textYouLost.push_back(glm::vec2(1.2, 3.2));
        textYouLost.push_back(glm::vec2(1.2, 3.2));
        textYouLost.push_back(glm::vec2(1.5, 0.2));
        textYouLost.push_back(glm::vec2(1.5, 3.2));

        textYouLost.push_back(glm::vec2(0.0, 0.2));
        textYouLost.push_back(glm::vec2(1.2, 0.2));
        textYouLost.push_back(glm::vec2(1.2, 0.5));
        textYouLost.push_back(glm::vec2(1.2, 0.5));
        textYouLost.push_back(glm::vec2(0.0, 0.2));
        textYouLost.push_back(glm::vec2(0.0, 0.5));

        // L
        textYouLost.push_back(glm::vec2(-3.8, -0.2));
        textYouLost.push_back(glm::vec2(-3.5, -0.2));
        textYouLost.push_back(glm::vec2(-3.5, -3.2));
        textYouLost.push_back(glm::vec2(-3.5, -3.2));
        textYouLost.push_back(glm::vec2(-3.8, -0.2));
        textYouLost.push_back(glm::vec2(-3.8, -3.2));

        textYouLost.push_back(glm::vec2(-3.8, -3.2));
        textYouLost.push_back(glm::vec2(-2.6, -3.2));
        textYouLost.push_back(glm::vec2(-2.6, -2.9));
        textYouLost.push_back(glm::vec2(-2.6, -2.9));
        textYouLost.push_back(glm::vec2(-3.8, -3.2));
        textYouLost.push_back(glm::vec2(-3.8, -2.9));

        // O
        textYouLost.push_back(glm::vec2(-1.8, -0.2));
        textYouLost.push_back(glm::vec2(-1.5, -0.2));
        textYouLost.push_back(glm::vec2(-1.5, -3.2));
        textYouLost.push_back(glm::vec2(-1.5, -3.2));
        textYouLost.push_back(glm::vec2(-1.8, -0.2));
        textYouLost.push_back(glm::vec2(-1.8, -3.2));

        textYouLost.push_back(glm::vec2(-0.3, -0.2));
        textYouLost.push_back(glm::vec2(-0.6, -0.2));
        textYouLost.push_back(glm::vec2(-0.6, -3.2));
        textYouLost.push_back(glm::vec2(-0.6, -3.2));
        textYouLost.push_back(glm::vec2(-0.3, -0.2));
        textYouLost.push_back(glm::vec2(-0.3, -3.2));

        textYouLost.push_back(glm::vec2(-1.8, -3.2));
        textYouLost.push_back(glm::vec2(-0.6, -3.2));
        textYouLost.push_back(glm::vec2(-0.6, -2.9));
        textYouLost.push_back(glm::vec2(-0.6, -2.9));
        textYouLost.push_back(glm::vec2(-1.8, -3.2));
        textYouLost.push_back(glm::vec2(-1.8, -2.9));

        textYouLost.push_back(glm::vec2(-1.8, -0.2));
        textYouLost.push_back(glm::vec2(-0.6, -0.2));
        textYouLost.push_back(glm::vec2(-0.6, -0.5));
        textYouLost.push_back(glm::vec2(-0.6, -0.5));
        textYouLost.push_back(glm::vec2(-1.8, -0.2));
        textYouLost.push_back(glm::vec2(-1.8, -0.5));

        // S
        textYouLost.push_back(glm::vec2(0.0, -0.2));
        textYouLost.push_back(glm::vec2(0.3, -0.2));
        textYouLost.push_back(glm::vec2(0.3, -1.6));
        textYouLost.push_back(glm::vec2(0.3, -1.6));
        textYouLost.push_back(glm::vec2(0.0, -0.2));
        textYouLost.push_back(glm::vec2(0.0, -1.6));

        textYouLost.push_back(glm::vec2(1.5, -1.8));
        textYouLost.push_back(glm::vec2(1.2, -1.8));
        textYouLost.push_back(glm::vec2(1.2, -3.2));
        textYouLost.push_back(glm::vec2(1.2, -3.2));
        textYouLost.push_back(glm::vec2(1.5, -1.8));
        textYouLost.push_back(glm::vec2(1.5, -3.2));

        textYouLost.push_back(glm::vec2(0.0, -3.2));
        textYouLost.push_back(glm::vec2(1.2, -3.2));
        textYouLost.push_back(glm::vec2(1.2, -2.9));
        textYouLost.push_back(glm::vec2(1.2, -2.9));
        textYouLost.push_back(glm::vec2(0.0, -3.2));
        textYouLost.push_back(glm::vec2(0.0, -2.9));

        textYouLost.push_back(glm::vec2(0.0, -0.2));
        textYouLost.push_back(glm::vec2(1.5, -0.2));
        textYouLost.push_back(glm::vec2(1.5, -0.5));
        textYouLost.push_back(glm::vec2(1.5, -0.5));
        textYouLost.push_back(glm::vec2(0.0, -0.2));
        textYouLost.push_back(glm::vec2(0.0, -0.5));

        textYouLost.push_back(glm::vec2(0.0, -1.6));
        textYouLost.push_back(glm::vec2(0.0, -1.9));
        textYouLost.push_back(glm::vec2(1.5, -1.9));
        textYouLost.push_back(glm::vec2(1.5, -1.9));
        textYouLost.push_back(glm::vec2(0.0, -1.6));
        textYouLost.push_back(glm::vec2(1.5, -1.6));

        // E
        textYouLost.push_back(glm::vec2(1.8, -0.2));
        textYouLost.push_back(glm::vec2(2.1, -0.2));
        textYouLost.push_back(glm::vec2(2.1, -3.2));
        textYouLost.push_back(glm::vec2(2.1, -3.2));
        textYouLost.push_back(glm::vec2(1.8, -0.2));
        textYouLost.push_back(glm::vec2(1.8, -3.2));

        textYouLost.push_back(glm::vec2(1.8, -3.2));
        textYouLost.push_back(glm::vec2(3.3, -3.2));
        textYouLost.push_back(glm::vec2(3.3, -2.9));
        textYouLost.push_back(glm::vec2(3.3, -2.9));
        textYouLost.push_back(glm::vec2(1.8, -3.2));
        textYouLost.push_back(glm::vec2(1.8, -2.9));

        textYouLost.push_back(glm::vec2(1.8, -0.2));
        textYouLost.push_back(glm::vec2(3.3, -0.2));
        textYouLost.push_back(glm::vec2(3.3, -0.5));
        textYouLost.push_back(glm::vec2(3.3, -0.5));
        textYouLost.push_back(glm::vec2(1.8, -0.2));
        textYouLost.push_back(glm::vec2(1.8, -0.5));

        textYouLost.push_back(glm::vec2(1.8, -1.6));
        textYouLost.push_back(glm::vec2(1.8, -1.9));
        textYouLost.push_back(glm::vec2(3.3, -1.9));
        textYouLost.push_back(glm::vec2(3.3, -1.9));
        textYouLost.push_back(glm::vec2(1.8, -1.6));
        textYouLost.push_back(glm::vec2(3.3, -1.6));
    }
    {
        // Y
        textYouWin.push_back(glm::vec2(-3, 2));
        textYouWin.push_back(glm::vec2(-4, 3));
        textYouWin.push_back(glm::vec2(-3.8, 3.2));
        textYouWin.push_back(glm::vec2(-3.8, 3.2));
        textYouWin.push_back(glm::vec2(-3, 2));
        textYouWin.push_back(glm::vec2(-2.8, 2.2));

        textYouWin.push_back(glm::vec2(-3, 2));
        textYouWin.push_back(glm::vec2(-2, 3));
        textYouWin.push_back(glm::vec2(-2.2, 3.2));
        textYouWin.push_back(glm::vec2(-2.2, 3.2));
        textYouWin.push_back(glm::vec2(-3, 2));
        textYouWin.push_back(glm::vec2(-3.2, 2.2));

        textYouWin.push_back(glm::vec2(-3.15, 2.2));
        textYouWin.push_back(glm::vec2(-2.85, 2.2));
        textYouWin.push_back(glm::vec2(-2.85, 0.2));
        textYouWin.push_back(glm::vec2(-2.85, 0.2));
        textYouWin.push_back(glm::vec2(-3.15, 2.2));
        textYouWin.push_back(glm::vec2(-3.15, 0.2));

        // O
        textYouWin.push_back(glm::vec2(-1.8, 0.2));
        textYouWin.push_back(glm::vec2(-1.5, 0.2));
        textYouWin.push_back(glm::vec2(-1.5, 3.2));
        textYouWin.push_back(glm::vec2(-1.5, 3.2));
        textYouWin.push_back(glm::vec2(-1.8, 0.2));
        textYouWin.push_back(glm::vec2(-1.8, 3.2));

        textYouWin.push_back(glm::vec2(-0.3, 0.2));
        textYouWin.push_back(glm::vec2(-0.6, 0.2));
        textYouWin.push_back(glm::vec2(-0.6, 3.2));
        textYouWin.push_back(glm::vec2(-0.6, 3.2));
        textYouWin.push_back(glm::vec2(-0.3, 0.2));
        textYouWin.push_back(glm::vec2(-0.3, 3.2));

        textYouWin.push_back(glm::vec2(-1.8, 3.2));
        textYouWin.push_back(glm::vec2(-0.6, 3.2));
        textYouWin.push_back(glm::vec2(-0.6, 2.9));
        textYouWin.push_back(glm::vec2(-0.6, 2.9));
        textYouWin.push_back(glm::vec2(-1.8, 3.2));
        textYouWin.push_back(glm::vec2(-1.8, 2.9));

        textYouWin.push_back(glm::vec2(-1.8, 0.2));
        textYouWin.push_back(glm::vec2(-0.6, 0.2));
        textYouWin.push_back(glm::vec2(-0.6, 0.5));
        textYouWin.push_back(glm::vec2(-0.6, 0.5));
        textYouWin.push_back(glm::vec2(-1.8, 0.2));
        textYouWin.push_back(glm::vec2(-1.8, 0.5));

        // U
        textYouWin.push_back(glm::vec2(0.0, 0.2));
        textYouWin.push_back(glm::vec2(0.3, 0.2));
        textYouWin.push_back(glm::vec2(0.3, 3.2));
        textYouWin.push_back(glm::vec2(0.3, 3.2));
        textYouWin.push_back(glm::vec2(0.0, 0.2));
        textYouWin.push_back(glm::vec2(0.0, 3.2));

        textYouWin.push_back(glm::vec2(1.5, 0.2));
        textYouWin.push_back(glm::vec2(1.2, 0.2));
        textYouWin.push_back(glm::vec2(1.2, 3.2));
        textYouWin.push_back(glm::vec2(1.2, 3.2));
        textYouWin.push_back(glm::vec2(1.5, 0.2));
        textYouWin.push_back(glm::vec2(1.5, 3.2));

        textYouWin.push_back(glm::vec2(0.0, 0.2));
        textYouWin.push_back(glm::vec2(1.2, 0.2));
        textYouWin.push_back(glm::vec2(1.2, 0.5));
        textYouWin.push_back(glm::vec2(1.2, 0.5));
        textYouWin.push_back(glm::vec2(0.0, 0.2));
        textYouWin.push_back(glm::vec2(0.0, 0.5));

        // W
        textYouWin.push_back(glm::vec2(-3.7, -0.2));
        textYouWin.push_back(glm::vec2(-3.4, -0.2));
        textYouWin.push_back(glm::vec2(-3.4, -3.2));
        textYouWin.push_back(glm::vec2(-3.4, -3.2));
        textYouWin.push_back(glm::vec2(-3.7, -0.2));
        textYouWin.push_back(glm::vec2(-3.7, -3.2));

        textYouWin.push_back(glm::vec2(-2.2, -0.2));
        textYouWin.push_back(glm::vec2(-2.5, -0.2));
        textYouWin.push_back(glm::vec2(-2.5, -3.2));
        textYouWin.push_back(glm::vec2(-2.5, -3.2));
        textYouWin.push_back(glm::vec2(-2.2, -0.2));
        textYouWin.push_back(glm::vec2(-2.2, -3.2));

        textYouWin.push_back(glm::vec2(-3.7, -3.2));
        textYouWin.push_back(glm::vec2(-1.3, -3.2));
        textYouWin.push_back(glm::vec2(-1.3, -2.9));
        textYouWin.push_back(glm::vec2(-1.3, -2.9));
        textYouWin.push_back(glm::vec2(-3.7, -3.2));
        textYouWin.push_back(glm::vec2(-3.7, -2.9));

        textYouWin.push_back(glm::vec2(-1.6, -0.2));
        textYouWin.push_back(glm::vec2(-1.3, -0.2));
        textYouWin.push_back(glm::vec2(-1.3, -3.2));
        textYouWin.push_back(glm::vec2(-1.3, -3.2));
        textYouWin.push_back(glm::vec2(-1.6, -0.2));
        textYouWin.push_back(glm::vec2(-1.6, -3.2));

        // I
        textYouWin.push_back(glm::vec2(-1.0, -0.2));
        textYouWin.push_back(glm::vec2(-0.7, -0.2));
        textYouWin.push_back(glm::vec2(-0.7, -3.2));
        textYouWin.push_back(glm::vec2(-0.7, -3.2));
        textYouWin.push_back(glm::vec2(-1.0, -0.2));
        textYouWin.push_back(glm::vec2(-1.0, -3.2));

        // N
        textYouWin.push_back(glm::vec2(-0.4, -0.2));
        textYouWin.push_back(glm::vec2(-0.1, -0.2));
        textYouWin.push_back(glm::vec2(-0.1, -3.2));
        textYouWin.push_back(glm::vec2(-0.1, -3.2));
        textYouWin.push_back(glm::vec2(-0.4, -0.2));
        textYouWin.push_back(glm::vec2(-0.4, -3.2));

        textYouWin.push_back(glm::vec2(1.1, -0.2));
        textYouWin.push_back(glm::vec2(1.4, -0.2));
        textYouWin.push_back(glm::vec2(1.4, -3.2));
        textYouWin.push_back(glm::vec2(1.4, -3.2));
        textYouWin.push_back(glm::vec2(1.1, -0.2));
        textYouWin.push_back(glm::vec2(1.1, -3.2));

        textYouWin.push_back(glm::vec2(-0.4, -0.2));
        textYouWin.push_back(glm::vec2(-0.1, -0.2));
        textYouWin.push_back(glm::vec2(1.1, -3.2));
        textYouWin.push_back(glm::vec2(1.1, -3.2));
        textYouWin.push_back(glm::vec2(-0.1, -0.2));
        textYouWin.push_back(glm::vec2(1.4, -3.2));
    }
    GLfloat vertex_buffer_data_YL[3 * textYouLost.size()];
    for (int a = 0; a < textYouLost.size(); a++)
    {
        vertex_buffer_data_YL[3 * a] = textYouLost[a].x;
        vertex_buffer_data_YL[3 * a + 1] = textYouLost[a].y;
        vertex_buffer_data_YL[3 * a + 2] = 0.0;
    }

    GLfloat vertex_buffer_data_YW[3 * textYouWin.size()];
    for (int a = 0; a < textYouWin.size(); a++)
    {
        vertex_buffer_data_YW[3 * a] = textYouWin[a].x;
        vertex_buffer_data_YW[3 * a + 1] = textYouWin[a].y;
        vertex_buffer_data_YW[3 * a + 2] = 0.0;
    }

    this->object[0] = create3DObject(GL_TRIANGLES, textYouLost.size(), vertex_buffer_data_YL, COLOR_WHITE, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, textYouWin.size(), vertex_buffer_data_YW, COLOR_WHITE, GL_FILL);
}

void GameOver::draw(glm::mat4 VP, int idx)
{
    glUniform1i(Light.StatusID, 1);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(position + this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[idx]);
}