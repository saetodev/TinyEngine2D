#ifndef TINY_ENGINE_APPLICATION_H
#define TINY_ENGINE_APPLICATION_H

#include "Basic.h"

struct GLFWwindow;

namespace Tiny {

struct Settings {
    int width;
    int height;
    std::string title;
};

class Application {
public:
    void Run();

    virtual void OnUpdate() = 0;
private:
    void Init();
    void Shutdown();
protected:
    Settings m_settings  = {};
    GLFWwindow* m_window = NULL;
};

}

#endif