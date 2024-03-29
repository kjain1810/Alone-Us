#include "coins.h"

Coin::Coin(float x, float y)
{
    this->position = glm::vec3(x, y, 0.0f);
    this->rotation = 0.0f;
    this->notTaken = true;
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f, // eyes begin
        0.0f, 1.0f, 0.0f,
        0.7f, 0.5f, 0.0f,
        0.3f, 0.5f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, // eyes end
    };

    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
}

void Coin::draw(glm::mat4 VP, float scale)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate * glm::scale(glm::vec3(scale, scale, scale)));
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}