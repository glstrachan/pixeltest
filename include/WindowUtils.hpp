#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#define WIDTH 480
#define HEIGHT 270

#define SCALE 3

void error_callback(int error, const char *description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

GLFWwindow *setupWindow() {
    glfwSetErrorCallback(error_callback);

    // Initialize GLFW
    if (!glfwInit()) std::cerr << "ERROR: could not start GLFW3" << std::endl;

    // Setting window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create the window
    GLFWwindow *window = glfwCreateWindow(WIDTH * SCALE, HEIGHT * SCALE, "2D Pixel Test", NULL, NULL);
    if (!window) {
        std::cerr << "ERROR: could not open window with GLFW3" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Very important idiot
    glEnable(GL_DEPTH_TEST); 

    return window;
}
