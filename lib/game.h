#pragma once

#include "cells.h"
#include "input.h"

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/mat4x4.hpp>
#include <utility>

const unsigned SCR_WIDTH = 1620;
const unsigned SCR_HEIGHT = 900;

class Game {
public:
    Game(std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned>, unsigned short);
    ~Game();

    void gameLoop();
    void mouseMotionCallback(double, double);
    void progressCallback(int, int, int, int);
private:
    void processInput(float);
    void initGame();

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

