#include "buttons.h"

Buttons::Buttons(float x, float y)
{
    this->position = glm::vec3(x, y, 0.0f);
    this->rotation = 0.0f;
    this->radius = 0.25f;
    GLfloat vertex_buffer_data[3 * 300];
    for (int a = 0; a < 300; a++)
    {
        vertex_buffer_data[3 * a] = this->radius * glm::cos(2 * a * M_PI / 300);     // X coord
        vertex_buffer_data[3 * a + 1] = this->radius * glm::sin(2 * a * M_PI / 300); // Y coord
        vertex_buffer_data[3 * a + 2] = 0.0f;                                        // Z coord
    }
    GLfloat all_vertex_buffer_data[299 * 3 * 3];
    for (int a = 0; a < 299; a++)
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
    this->object = create3DObject(GL_TRIANGLE_FAN, 299 * 3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Buttons::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}