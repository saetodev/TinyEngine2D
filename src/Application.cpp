#include "Application.h"
#include "Renderer2D.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Tiny {

void Application::Run() {
    Init();

    while (!glfwWindowShouldClose(m_window)) {
        OnUpdate();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    Shutdown();
}

void Application::Init() {
    if (!glfwInit()) {
        const char* message = NULL;
        glfwGetError(&message);

        std::cout << "ERROR: " << message << std::endl;
        std::exit(-1);
    }

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    m_window = glfwCreateWindow(m_settings.width, m_settings.height, m_settings.title.c_str(), NULL, NULL);

    if (!m_window) {
        const char* message = NULL;
        glfwGetError(&message);

        std::cout << "ERROR: " << message << std::endl;
        std::exit(-1);
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to load OpenGL" << std::endl;
        std::exit(-1);
    }

    Renderer2D::Init();
}

void Application::Shutdown() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

}