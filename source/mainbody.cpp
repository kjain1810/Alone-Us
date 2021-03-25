#include "mainbody.h"

Mainbody::Mainbody(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        -0.1f, -0.15f, 0.0f, // triangle 1 : begin
        0.1f, -0.15f, 0.0f,
        -0.1f, 0.15f, 0.0f, // triangle 1 : end
        0.1f, 0.15f, 0.0f,  // triangle 2 : begin
        0.1f, -0.15f, 0.0f,
        -0.1f, 0.15f, 0.0f,  // triangle 2 : end
        -0.1f, -0.15f, 0.0f, // left leg begin
        -0.04f, -0.15f, 0.0f,
        -0.1f, -0.24f, 0.0f,
        -0.1f, -0.24f, 0.0f,
        -0.04f, -0.15f, 0.0f,
        -0.04f, -0.24f, 0.0f, // left leg end
        0.1f, -0.15f, 0.0f,   // right leg begin
        0.04f, -0.15f, 0.0f,
        0.1f, -0.24f, 0.0f,
        0.1f, -0.24f, 0.0f,
        0.04f, -0.15f, 0.0f,
        0.04f, -0.24f, 0.0f, // right leg end
        -0.1f, 0.12f, 0.0f,  // backpack begin
        -0.1f, -0.12f, 0.0f,
        -0.15f, -0.12f, 0.0f,
        -0.15f, -0.12f, 0.0f,
        -0.1f, 0.12f, 0.0f,
        -0.15f, 0.12f, 0.0f, // backpack end
    };

    this->object = create3DObject(GL_TRIANGLES, 8 * 3, vertex_buffer_data, color, GL_FILL);
}

void Mainbody::draw(glm::mat4 VP, glm::vec3 position)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(position + this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}