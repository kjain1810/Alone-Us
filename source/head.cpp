#include "head.h"

Head::Head(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    GLfloat vertex_buffer_data[3 * 100];
    for (int a = 0; a < 100; a++)
    {
        vertex_buffer_data[3 * a] = 0.09 * glm::cos(a * M_PI / 100);            // X coord
        vertex_buffer_data[3 * a + 1] = 0.15f + 0.1 * glm::sin(a * M_PI / 100); // Y coord
        vertex_buffer_data[3 * a + 2] = 0.0f;                                   // Z coord
    }
    GLfloat all_vertex_buffer_data[99 * 3 * 3];
    for (int a = 0; a < 99; a++)
    {
        all_vertex_buffer_data[9 * a] = 0.0f;
        all_vertex_buffer_data[9 * a + 1] = 0.0f;
        all_vertex_buffer_data[9 * a + 2] = 0.0f;
        all_vertex_buffer_data[9 * a + 3] = vertex_buffer_data[3 * a];
        all_vertex_buffer_data[9 * a + 4] = vertex_buffer_data[3 * a + 1];
        all_vertex_buffer_data[9 * a + 5] = 0.0f;
        all_vertex_buffer_data[9 * a + 6] = vertex_buffer_data[3 * (a + 1)];
        all_vertex_buffer_data[9 * a + 7] = vertex_buffer_data[3 * (a + 1) + 1];
        all_vertex_buffer_data[9 * a + 8] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLE_FAN, 99 * 3, vertex_buffer_data, color, GL_FILL);
}

void Head::draw(glm::mat4 VP, glm::vec3 position)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(position + this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}