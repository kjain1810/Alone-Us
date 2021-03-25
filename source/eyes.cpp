#include "eyes.h"

Eyes::Eyes(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.08f, 0.0f, // eyes begin
        0.0f, 0.02f, 0.0f,
        0.15f, 0.02f, 0.0f,
        0.15f, 0.02f, 0.02f,
        0.0f, 0.08f, 0.0f,
        0.15f, 0.08f, 0.0f, // eyes end
    };

    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void Eyes::draw(glm::mat4 VP, glm::vec3 position)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(position + this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}