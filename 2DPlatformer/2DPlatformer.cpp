#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gen/color.hpp>
#include <engine/camera.hpp>
#include <engine/shader.hpp>
#include <engine/mesh.hpp>
#include <engine/sprite.hpp>
#include <engine/texture.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    // culling won't make sense for 2D, but use it for debugging to make sure all faces have consistent winding order
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    Camera2D camera;
    camera.setProjection(SCR_WIDTH, SCR_HEIGHT);

    std::unique_ptr<Shader> flatShader(new Shader());
    std::unique_ptr<Tex2D_URGB> sampleTex(new Tex2D_URGB());

    // TODO: add path utilities
    sampleTex->loadFromFile("../resources/textures/brick.png");
    flatShader->loadFromFile("../shaders/flatShaderVert.glsl", "../shaders/flatShaderFrag.glsl");
    Sprite sprite(std::make_unique<MBox2D>(0.5f, 0.5f), flatShader.get());
    sprite.addTexture(sampleTex->getID());

    float phase = 0.0f;
    auto curTime = std::chrono::high_resolution_clock::now();
    Color_FRGBA clearColor(0.1f, 0.1f, 0.1f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(clearColor.r(), clearColor.g(), clearColor.b(), clearColor.a());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sprite.render(camera);

        glfwSwapBuffers(window);
        glfwPollEvents();

        {
            auto nextTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(nextTime - curTime).count() / 1e6;
            sprite.setPosition(glm::vec3(sin(phase), 0.0f, 0.0f));
            sprite.rotate(deltaTime * 3.1416 / 2.0f);
            phase += deltaTime * 3.1416f / 2.0f;
            if (phase >= 3.1416 * 2.0f) phase = 0.0f;
        }

        curTime = std::chrono::high_resolution_clock::now();
    }

    glfwTerminate();
    return 0;
}