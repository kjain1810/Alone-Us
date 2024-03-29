#include "main.h"
#include "timer.h"
#include "ball.h"
#include "game.h"

#include <time.h>

using namespace std;

GLMatrices Matrices;
GLLighting Light;
Camera camera;
GLuint programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Game game;

int timer = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

float move_x = 0.05;
float move_y = 0.05;

Timer t60(1.0 / 60);

clock_t startTime, curTime, lightTime;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw()
{
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(camera.eye, camera.target, camera.up); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP; // MVP = Projection * View * Model

    // Scene render
    if (game.gameStatus == 0)
        game.draw(VP);
    else
    {
        camera.eye = glm::vec3(0.0f, 0.0f, 5.0f);
        camera.target = glm::vec3(0.0f, 0.0f, 0.0f);
        Matrices.view = glm::lookAt(camera.eye, camera.target, camera.up); // Rotating Camera for 3D
        glm::mat4 VP = Matrices.projection * Matrices.view;
        game.gameover.draw(VP, game.gameStatus - 1);
    }
}

void tick_input(GLFWwindow *window)
{
    if (game.gameStatus)
        return;
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);
    if (left)
    {
        // move things to the left
        if (game.movePlayer(-move_x, 0))
        {
            camera.eye.x -= move_x;
            camera.target.x -= move_x;
        }
    }
    if (right)
    {
        // move things to the right
        if (game.movePlayer(move_x, 0))
        {
            camera.eye.x += move_x;
            camera.target.x += move_x;
        }
    }
    if (up)
    {
        // move things up
        if (game.movePlayer(0, move_y))
        {
            camera.eye.y += move_y;
            camera.target.y += move_y;
        }
    }
    if (down)
    {
        // move things down
        if (game.movePlayer(0, -move_y))
        {
            camera.eye.y -= move_y;
            camera.target.y -= move_y;
        }
    }
    if (a)
        game.pressButtons();
    if (s && (curTime - lightTime) / CLOCKS_PER_SEC >= 1)
    {
        game.switchLights();
        lightTime = curTime;
    }
}

void tick_elements()
{
    if (game.gameStatus)
        return;
    game.moveImposter();
    timer++;
    curTime = clock();
    if (timer == 60)
    {
        timer = 0;
        game.decreaseHealth();
    }
    game.gameStatus = game.checkContinue();
    if (game.gameStatus)
        sleep(2);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    game = Game(12, 12, COLOR_PURPLE, COLOR_RED, COLOR_BLACK, COLOR_WHITE);
    camera.eye = glm::vec3(0.0f, -12.0f, 5.0f);
    camera.target = glm::vec3(0.0f, -12.0f, 0.0f);
    camera.up = glm::vec3(0.0f, 1.0f, 0.0f);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Light.LocationID = glGetUniformLocation(programID, "location");
    Light.StatusID = glGetUniformLocation(programID, "status");
    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_GREY.r / 256.0, COLOR_GREY.g / 256.0, COLOR_GREY.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv)
{
    startTime = clock();
    srand(time(0));
    int width = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process timers

        if (t60.processTick())
        {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b)
{
    return (a.x + a.width >= b.x) && (b.x + b.width >= a.x) && (a.y + a.height >= b.y) && (b.y + b.height >= a.y);
}

void reset_screen()
{
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

bool circleRectIntersect(bounding_box_t playerbb, float radius, glm::vec3 center)
{
    float distX = abs(center.x - playerbb.x);
    float distY = abs(center.y - playerbb.y);
    if (distX > playerbb.width / 2 + radius || distY > playerbb.height / 2 + radius)
        return false;
    float cornerdist = (distX - playerbb.width / 2) * (distX - playerbb.width / 2) + (distY - playerbb.height / 2) * (distY - playerbb.height / 2);
    if (distX <= playerbb.width || distY <= playerbb.height || cornerdist <= radius * radius)
        return true;
    return false;
}

bool check_inside(bounding_box_t a, bounding_box_t b)
{
    bool ret = (a.x <= b.x) && (a.x + a.width >= b.x + b.width) && (a.y <= b.y) && (a.y + a.height >= b.y + b.width);
    ret |= (b.x <= a.x) && (b.x + b.width >= a.x + a.width) && (b.y <= a.y) && (b.y + b.height >= a.y + a.width);
    return ret;
}