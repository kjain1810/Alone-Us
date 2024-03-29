#include "entryexit.h"

EntryExit::EntryExit(float x, float y)
{
    this->position = glm::vec3(x, y, 0.0);
    this->rotation = 0.0f;
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f, // eyes begin
        1.5f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.5f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.5f, 1.0f, 0.0f, // eyes end
    };

    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void EntryExit::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}