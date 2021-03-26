#include "main.h"
#include "maze.h"

#include <vector>
#include <random>
#include <time.h>

Maze::Maze(float height, float width)
{
    srand(time(NULL));
    this->height = height;
    this->width = width;
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    std::vector<glm::vec3> vec;
    std::vector<glm::vec3> vertices;
    glm::vec3 vert1, vert2, vert3, vert4;
    // WALLS
    // down wall
    vert1 = glm::vec3(-16.0f, -16.0f, 0.0f);
    vert2 = glm::vec3(-16.0f, -12.0f, 0.0f);
    vert3 = glm::vec3(16.0f, -12.0f, 0.0f);
    vert4 = glm::vec3(16.0f, -16.0f, 0.0f);
    this->createSquare(vert1, vert2, vert3, vert4, vec);
    // left wall
    vert1 = glm::vec3(-16.0f, -16.0f, 0.0f);
    vert2 = glm::vec3(-16.0f, 16.0f, 0.0f);
    vert3 = glm::vec3(-12.0f, 16.0f, 0.0f);
    vert4 = glm::vec3(-12.0f, -16.0f, 0.0f);
    this->createSquare(vert1, vert2, vert3, vert4, vec);
    // up wall
    vert1 = (glm::vec3(-16.0f, 12.0f, 0.0f));
    vert2 = (glm::vec3(-16.0f, 16.0f, 0.0f));
    vert3 = (glm::vec3(16.0f, 16.0f, 0.0f));
    vert4 = (glm::vec3(16.0f, 12.0f, 0.0f));
    this->createSquare(vert1, vert2, vert3, vert4, vec);
    // right wall
    vert1 = (glm::vec3(12.0f, -16.0f, 0.0f));
    vert2 = (glm::vec3(12.0f, 16.0f, 0.0f));
    vert3 = (glm::vec3(16.0f, 16.0f, 0.0f));
    vert4 = (glm::vec3(16.0f, -16.0f, 0.0f));
    this->createSquare(vert1, vert2, vert3, vert4, vec);
    float X_large[] = {-4.0f, 4.0f}, Y_large[] = {-4.0f, 4.0f};
    for (int a = 0; a < 2; a++)
        for (int b = 0; b < 2; b++)
        {
            float y_diff = (float)(rand() % 4000 - 2000) / 1000.0f;
            float side = 1.5f + ((float)(std::rand() % 700)) / 1000.0f;
            vert1 = glm::vec3(X_large[a] - side / 2.0f, Y_large[b] - side / 2.0f + y_diff, 0.0f);
            vert2 = glm::vec3(X_large[a] - side / 2.0f, Y_large[b] + side / 2.0f + y_diff, 0.0f);
            vert3 = glm::vec3(X_large[a] + side / 2.0f, Y_large[b] + side / 2.0f + y_diff, 0.0f);
            vert4 = glm::vec3(X_large[a] + side / 2.0f, Y_large[b] - side / 2.0f + y_diff, 0.0f);
            this->createSquare(vert1, vert2, vert3, vert4, vec);
        }
    float X_small_1[] = {-8, 0, 8}, Y_small_1[] = {12, 4, -4, -12};
    for (int a = 0; a < 3; a++)
        for (int b = 0; b < 4; b++)
        {
            if (a == 1 && (b == 3 || b == 0))
                continue;
            float y_diff = (float)(rand() % 4000 - 2000) / 1000.0f;
            float side = 1.0f + ((float)(std::rand() % 700)) / 1000.0f;
            vert1 = glm::vec3(X_small_1[a] - side / 2.0f, Y_small_1[b] - side / 2.0f + y_diff, 0.0f);
            vert2 = glm::vec3(X_small_1[a] - side / 2.0f, Y_small_1[b] + side / 2.0f + y_diff, 0.0f);
            vert3 = glm::vec3(X_small_1[a] + side / 2.0f, Y_small_1[b] + side / 2.0f + y_diff, 0.0f);
            vert4 = glm::vec3(X_small_1[a] + side / 2.0f, Y_small_1[b] - side / 2.0f + y_diff, 0.0f);
            this->createSquare(vert1, vert2, vert3, vert4, vec);
        }
    float X_small_2[] = {12, 4, -4, -12}, Y_small_2[] = {-8, 0, 8};
    for (int a = 0; a < 4; a++)
        for (int b = 0; b < 3; b++)
        {
            if (a == 3 && b == 1)
                continue;
            float y_diff = (float)(rand() % 4000 - 2000) / 1000.0f;
            float side = 1.0f + ((float)(std::rand() % 700)) / 1000.0f;
            vert1 = glm::vec3(X_small_2[a] - side / 2.0f, Y_small_2[b] - side / 2.0f + y_diff, 0.0f);
            vert2 = glm::vec3(X_small_2[a] - side / 2.0f, Y_small_2[b] + side / 2.0f + y_diff, 0.0f);
            vert3 = glm::vec3(X_small_2[a] + side / 2.0f, Y_small_2[b] + side / 2.0f + y_diff, 0.0f);
            vert4 = glm::vec3(X_small_2[a] + side / 2.0f, Y_small_2[b] - side / 2.0f + y_diff, 0.0f);
            this->createSquare(vert1, vert2, vert3, vert4, vec);
        }
    float X_small_3[] = {-8, 0, 8}, Y_small_3[] = {-8, 0, 8};
    for (int a = 0; a < 3; a++)
        for (int b = 0; b < 3; b++)
        {
            float y_diff = (float)(rand() % 4000 - 2000) / 1000.0f;
            float side = 0.5f + ((float)(std::rand() % 500)) / 1000.0f;
            vert1 = glm::vec3(X_small_3[a] - side / 2.0f, Y_small_3[b] - side / 2.0f + y_diff, 0.0f);
            vert2 = glm::vec3(X_small_3[a] - side / 2.0f, Y_small_3[b] + side / 2.0f + y_diff, 0.0f);
            vert3 = glm::vec3(X_small_3[a] + side / 2.0f, Y_small_3[b] + side / 2.0f + y_diff, 0.0f);
            vert4 = glm::vec3(X_small_3[a] + side / 2.0f, Y_small_3[b] - side / 2.0f + y_diff, 0.0f);
            this->createSquare(vert1, vert2, vert3, vert4, vec);
        }
    GLfloat vertex_buffer_data[3 * vec.size()];
    for (int a = 0; a < vec.size(); a++)
    {
        vertex_buffer_data[3 * a] = vec[a].x;
        vertex_buffer_data[3 * a + 1] = vec[a].y;
        vertex_buffer_data[3 * a + 2] = vec[a].z;
    }
    this->object = create3DObject(GL_TRIANGLES, vec.size(), vertex_buffer_data, COLOR_WALL, GL_FILL);
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

void Maze::createSquare(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4, std::vector<glm::vec3> &vec)
{
    vec.push_back(v1);
    vec.push_back(v2);
    vec.push_back(v3);
    vec.push_back(v1);
    vec.push_back(v3);
    vec.push_back(v4);
    std::vector<glm::vec3> here;
    here.push_back(v1); // BOTTOM LEFT
    here.push_back(v2); // TOP LEFT
    here.push_back(v3); // TOP RIGHT
    here.push_back(v4); // BOTTOM RIGHT
    this->walls.push_back(here);
}