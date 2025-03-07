#include "Application.h"
#include "Renderer2D.h"
#include "Window.h"

void Tiny::Application::Run() {
    Init();

    while (!Window::Closed()) {
        OnUpdate();
        Window::SwapBuffers();
    }

    Shutdown();
}

void Tiny::Application::Init() {
    Window::Init(m_settings.width, m_settings.height, m_settings.title);
    Renderer2D::Init();
}

void Tiny::Application::Shutdown() {
    Window::Shutdown();
    Renderer2D::Shutdown();
}