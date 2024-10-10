#include "glad/glad.h"
#include "game.h"

#include <iostream>

Game::Game(std::pair<unsigned, unsigned> survival, std::pair<unsigned, unsigned> birth, uint_fast8_t lifetime, unsigned short neighbourhood) {
    initGame();
    cells = new Cells{survival, birth, lifetime, neighbourhood};
}

Game::~Game() {
    delete cells;
    glfwTerminate();
}

void Game::initGame() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Cellular Automata", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create window" << std::endl;
    }

    glfwMakeContextCurrent(window);

    //glfwSwapInterval(0);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glfwSetWindowUserPointer(window, this);
    auto mouseMotionCallback = [](GLFWwindow* w, double x, double y) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))
            ->mouseMotionCallback(x, y);
    };
    glfwSetCursorPosCallback(window, mouseMotionCallback);

    glfwSetWindowUserPointer(window, this);
    auto keyCallback = [](GLFWwindow* w, int key, int scancode, int actions, int mods) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))
            ->progressCallback(key, scancode, actions, mods);
    };
    glfwSetKeyCallback(window, keyCallback);


    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }

    camera = new Camera{};
}

void Game::gameLoop() {
    float currentFrame = 0.0f;
    glfwSetTime(0);
    cells->generateMesh();
    while (!glfwWindowShouldClose(window)) {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera->lookAt();

        cells->draw(view);

        processInput(deltaTime);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Game::processInput(float delta) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    camera->processMovement(window, delta);
}

void Game::mouseMotionCallback(double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(window, xoffset, yoffset);
}

void Game::progressCallback(int key, int scancode, int actions, int mods) {
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        cells->progress();
        //std::cout << "Progressed one step" << std::endl;
    }
}


void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    (void)window; // Unused
    glViewport(0, 0, width, height);
}

