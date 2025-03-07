#ifndef TINY_ENGINE_RENDERER2D_H
#define TINY_ENGINE_RENDERER2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tiny::Renderer2D {
    void Init();
    void Shutdown();
    
    void Begin();
    void End();

    void Clear(glm::vec4 color);
    void DrawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color);
}

#endif