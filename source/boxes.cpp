#include "boxes.h"

Box::Box(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0.0f);
    this->rotation = 0.0f;
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f, // triangle 1 : begin
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, // triangle 1 : end
        1.0f, 0.0f, 0.0f, // triangle 2 : begin
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, color, GL_FILL);
}

void Box::draw(glm::mat4 VP, glm::vec3 position, float scale)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(position + this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate * glm::scale(glm::vec3(scale, scale, scale)));
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}