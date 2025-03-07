cmake_minimum_required(VERSION 3.30)

project(TinyEngine2D)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

include_directories("include")

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} "vendor/glad/src/glad.c")

if(WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC "vendor/glfw/include" "vendor/glad/include" "vendor/glm")
    target_link_directories(${PROJECT_NAME} PUBLIC "vendor/glfw/lib-vc2022")
    target_link_libraries(${PROJECT_NAME} "glfw3" "opengl32")
endif()