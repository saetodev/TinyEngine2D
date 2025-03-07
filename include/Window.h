#ifndef TINY_ENGINE_WINDOW_H
#define TINY_ENGINE_WINDOW_H

#include "Basic.h"

namespace Tiny::Window {
    void Init(int width, int height, const std::string& title);
    void Shutdown();

    void SwapBuffers();

    bool Closed();
}

#endif