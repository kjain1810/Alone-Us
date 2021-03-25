#include "player.h"

Player::Player(int x, int y)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, // triangle 1 : begin
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, // triangle 1 : end
        1.0f, 1.0f, 0.0f,  // triangle 2 : begin
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, // triangle 2 : end
    };
    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void Player::draw(glm::mat4 VP)
{
    // std::cout << "Player: " << this->position.x << " " << this->position.y << " " << this->position.z << "\n";
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::move(float x, float y)
{
    this->position.x += x;
    this->position.y += y;
}