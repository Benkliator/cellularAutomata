#include "input.h"
#include <iostream>

Camera::Camera() {}

glm::mat4 Camera::lookAt() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::processMouseMovement(GLFWwindow* window,
                                  double xoffset,
                                  double yoffset,
                                  GLboolean constrainPitch) {
    (void)window; // Unused
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(cameraFront);
}

void Camera::processMovement(GLFWwindow* window, float delta) {
    float horizontalSpeed = 4.0;
    float verticalSpeed = 1.0;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        velocity += glm::normalize(glm::vec3(cameraFront.x, 0, cameraFront.z)) * horizontalSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        velocity -= glm::normalize(glm::vec3(cameraFront.x, 0, cameraFront.z)) * horizontalSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        velocity -= glm::normalize(glm::cross(glm::vec3(cameraFront.x, 0, cameraFront.z), cameraUp)) * horizontalSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        velocity += glm::normalize(glm::cross(glm::vec3(cameraFront.x, 0, cameraFront.z), cameraUp)) * horizontalSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        velocity.y += verticalSpeed * 3;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        velocity.y -= verticalSpeed * 3;
    }


    velocity.y /= 1.8;
    velocity.x /= 2.8;
    velocity.z /= 2.8;

    cameraPos += velocity * delta;
}
