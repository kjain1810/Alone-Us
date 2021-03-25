#include "main.h"
#include "maze.h"

Maze::Maze(float height, float width)
{
    this->height = height;
    this->width = width;
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        -3.0f, -3.0f, 0.0f, // triangle 1 : begin
        3.0f, -3.0f, 0.0f,
        -3.0f, 3.0f, 0.0f, // triangle 1 : end
        3.0f, 3.0f, 0.0f,  // triangle 2 : begin
        3.0f, -3.0f, 0.0f,
        -3.0f, 3.0f, 0.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Maze::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}