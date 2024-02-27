#define STB_IMAGE_IMPLEMENTATION

#include <game/main.hpp>

#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gen/color.hpp>
#include <gen/path.hpp>
#include <engine/camera.hpp>
#include <engine/shader.hpp>
#include <engine/mesh.hpp>
#include <engine/sprite.hpp>
#include <engine/texture.hpp>
#include <engine/buffer.hpp>

#include <game/globalStore.hpp>

MainWindow::MainWindow(int _width, int _height)
:Window(_width, _height) { };

void MainWindow::init() {
    mCharacterTex = std::make_unique<Tex2D_URGB>();
    mCharacter.setMesh(std::make_unique<MBox2D>(0.25f, 0.25f));
    mCharacter.setShader(std::make_unique<Shader>(*GlobalStoreSingleton::getShader("defaultFlat")));
    mCharacterTex->loadFromFile(path::root()/"resources"/"textures"/"brick.png");
    mCharacter.setTexture(0, mCharacterTex->getID());
}

void MainWindow::renderLoop(float _deltaTime) {
    static float phase = 0.0f;
    
    mFrameBuffer->use();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mCharacter.setPosition(glm::vec3(sin(phase), 0.0f, 0.0f));
    mCharacter.rotate(_deltaTime * 3.1416 / 2.0f);
    phase += _deltaTime * 3.1416f / 2.0f;
    if (phase >= 3.1416 * 2.0f) phase = 0.0f;

    mCharacter.render(*mCamera);

    mFrameBuffer->discard();
    renderToWindow();
}

void MainWindow::onResize() {

}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    MainWindow mainWindow(1000, 800);
    mainWindow.createWindow("2D Platformer");
    glfwMakeContextCurrent(mainWindow.getWindowHandle());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    glCullFace(GL_FRONT); // culling won't make sense for 2D, but use it for debugging to make sure all faces have consistent winding order
    glFrontFace(GL_CW);

    GlobalStoreSingleton::init();
    mainWindow.createResources(GlobalStoreSingleton::getShader("defaultFlat"));
    mainWindow.init();

    auto time = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(mainWindow.getWindowHandle())) {
        auto curTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - time).count() / 1e6;
        time = curTime;

        mainWindow.renderLoop(deltaTime);

        glfwSwapBuffers(mainWindow.getWindowHandle());
        glfwPollEvents(); // TODO: handle events on a different thread
    }

    glfwTerminate();
    return 0;
}