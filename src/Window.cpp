#include "Window.h"
#include "Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static GLFWwindow* s_window;

struct InputButton {
    bool down;
    bool pressed;
    bool released;
};

static std::array<InputButton, Tiny::NUM_KEY_CODES> s_keys;

static void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key < 0 || key >= s_keys.size()) {
        return;
    }

    bool isDown  = (action == GLFW_PRESS)   || (action == GLFW_REPEAT);
    bool wasDown = (action == GLFW_RELEASE) || (action == GLFW_REPEAT);

    s_keys[key].down = isDown;
    s_keys[key].pressed = isDown && !wasDown;
    s_keys[key].released = !isDown && wasDown;
}

void Tiny::Window::Init(int width, int height, const std::string& title) {
    if (!glfwInit()) {
        const char* message = NULL;
        glfwGetError(&message);

        std::cout << "ERROR: " << message << std::endl;
        std::exit(-1);
    }

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    s_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!s_window) {
        const char* message = NULL;
        glfwGetError(&message);

        std::cout << "ERROR: " << message << std::endl;
        std::exit(-1);
    }

    glfwSetKeyCallback(s_window, WindowKeyCallback);

    glfwMakeContextCurrent(s_window);

    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to load OpenGL" << std::endl;
        std::exit(-1);
    }
}

void Tiny::Window::Shutdown() {
    glfwDestroyWindow(s_window);
    glfwTerminate();
}

void Tiny::Window::SwapBuffers() {
    for (InputButton& key : s_keys) {
        key.pressed  = false;
        key.released = false;
    }

    glfwSwapBuffers(s_window);
    glfwPollEvents();
}

bool Tiny::Window::Closed() {
    glfwWindowShouldClose(s_window);
}

bool Tiny::Input::KeyDown(KeyCode key) {
    return s_keys[key].down;
}

bool Tiny::Input::KeyPressed(KeyCode key) {
    return s_keys[key].pressed;
}

bool Tiny::Input::KeyReleased(KeyCode key) {
    return s_keys[key].released;
}