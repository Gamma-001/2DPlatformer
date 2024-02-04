#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine/camera.hpp>
#include <engine/shader.hpp>
#include <engine/mesh.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "2D Platformer", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Camera2D camera;
    camera.setProjection(SCR_WIDTH, SCR_HEIGHT);
    Shader flatShader;
    
    // TODO: add path utilities
    flatShader.loadFromFile("../shaders/flatShaderVert.glsl", "../shaders/flatShaderFrag.glsl");
    std::unique_ptr<Mesh2D> box = std::make_unique<MBox2D>(0.5f, 0.5f);

    float phase = 0.0f;
    auto curTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        box->render(flatShader, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();

        {
            auto nextTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(nextTime - curTime).count() / 1e6;
            box->setPosition(glm::vec3(sin(phase), 0.0f, 0.0f));
            box->rotate(deltaTime * 3.1416 / 2.0f);
            phase += deltaTime * 3.1416f / 2.0f;
            if (phase >= 3.1416 * 2.0f) phase = 0.0f;
        }

        curTime = std::chrono::high_resolution_clock::now();
    }

    glfwTerminate();
    return 0;
}