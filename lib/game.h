#pragma once

#include "cells.h"
#include "input.h"

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/mat4x4.hpp>

const unsigned SCR_WIDTH = 1620;
const unsigned SCR_HEIGHT = 900;

class Game {
public:
    Game();
    ~Game();

    void gameLoop();
    void mouseMotionCallback(double, double);
    void progressCallback(int, int, int, int);
private:
    void processInput(float);

    Cells* cells = nullptr;
    Camera* camera = nullptr;
    GLFWwindow* window = nullptr;

    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};

void framebufferSizeCallback(GLFWwindow*, int, int);

