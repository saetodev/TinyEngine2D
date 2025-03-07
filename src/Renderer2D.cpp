#include "Basic.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Tiny::Renderer2D {

struct RectVertex {
    glm::vec4 position;
    glm::vec4 color;
};

static constexpr int VERTICES_PER_RECT = 6;
static constexpr int MAX_RENDER_COUNT  = 1000;

static u32 s_rectVBO;
static u32 s_rectShader;
static u32 s_rectCount;
std::vector<RectVertex> s_rectVertexBuffer;

static glm::mat4 s_projection;

std::string ReadEntireFile(const std::string& filename) {
    std::string line;
    std::fstream file(filename);

    std::stringstream stream;

    while (std::getline(file, line)) {
        stream << line << "\n";
    }

    return stream.str();
}

u32 LoadShader(const std::string& vertexFilename, const std::string& fragmentFilename) {
    std::string vertexSource   = ReadEntireFile(vertexFilename);
    std::string fragmentSource = ReadEntireFile(fragmentFilename);

    const char* vertexSourceRaw   = vertexSource.c_str();
    const char* fragmentSourceRaw = fragmentSource.c_str();

    u32 program = glCreateProgram();

    u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSourceRaw, NULL);
    glCompileShader(vertexShader);

    {
        int result = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE) {
            int messageLen;
            char message[256];

            glGetShaderInfoLog(vertexShader, 256, &messageLen, message);

            std::cout << "ERROR: Failed to compile vertex shader\n" << message << std::endl;
            return 0;
        }
    }

    u32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSourceRaw, NULL);
    glCompileShader(fragmentShader);

    {
        int result = 0;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE) {
            int messageLen;
            char message[256];

            glGetShaderInfoLog(fragmentShader, 256, &messageLen, message);

            std::cout << "ERROR: Failed to compile fragment shader\n" << message << std::endl;
            return 0;
        }
    }

    glBindAttribLocation(program, 0, "a_position");
    glBindAttribLocation(program, 1, "a_color");

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Init() {
    glGenBuffers(1, &s_rectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, s_rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(RectVertex) * VERTICES_PER_RECT * MAX_RENDER_COUNT, NULL, GL_DYNAMIC_DRAW);

    s_rectShader = LoadShader("rect_vertex.glsl", "rect_fragment.glsl");
    glUseProgram(s_rectShader);

    s_rectVertexBuffer.reserve(VERTICES_PER_RECT * MAX_RENDER_COUNT);

    s_projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 1.0f);
}

void Flush() {
    glGenBuffers(1, &s_rectVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(RectVertex) * s_rectVertexBuffer.size(), s_rectVertexBuffer.data());

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(RectVertex), (const void*)offsetof(RectVertex, position));
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(RectVertex), (const void*)offsetof(RectVertex, color));

    glDrawArrays(GL_TRIANGLES, 0, s_rectVertexBuffer.size());

    s_rectVertexBuffer.clear();
}

void Begin() {
    int loc = glGetUniformLocation(s_rectShader, "u_projection");
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(s_projection));
}

void End() {
    Flush();
}

void Clear(glm::vec4 color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DrawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color) {
    if (s_rectCount == MAX_RENDER_COUNT) {
        Flush();
    }

    constexpr glm::vec4 vertices[VERTICES_PER_RECT] = {
        { -0.5f, -0.5f, 0.0f, 1.0f },
        {  0.5f, -0.5f, 0.0f, 1.0f },
        {  0.5f,  0.5f, 0.0f, 1.0f },

        {  0.5f,  0.5f, 0.0f, 1.0f },
        { -0.5f,  0.5f, 0.0f, 1.0f },
        { -0.5f, -0.5f, 0.0f, 1.0f },
    };

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

    for (int i = 0; i < VERTICES_PER_RECT; i++) {
        RectVertex vertex = {
            .position = transform * vertices[i],
            .color    = color,   
        };

        s_rectVertexBuffer.push_back(vertex);
    }

    s_rectCount++;
}

}