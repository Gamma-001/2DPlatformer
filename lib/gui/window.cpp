#include <gui/window.hpp>

#include <stdexcept>
#include <cassert>

#include <engine/shader.hpp>
#include <engine/mesh.hpp>
#include <gen/path.hpp>

Window::Window(int _widht, int _height)
:mWidth(_widht)
,mHeight(_height)
,mWindow(nullptr)
,mClearColor(1.0f, 1.0f, 1.0f, 1.0f) {}

Window::~Window() {
    if (mWindow != nullptr) glfwDestroyWindow(mWindow);
}

void Window::createWindow(const std::string& _title, bool _resizable) {
    assert(mHeight != 0 && mWidth != 0);
    
    glfwWindowHint(GLFW_RESIZABLE, _resizable? GLFW_TRUE: GLFW_FALSE);
    mWindow = glfwCreateWindow(mWidth, mHeight, _title.c_str(), nullptr, nullptr);
    if (mWindow == nullptr) throw std::runtime_error("Failed to create glfw window");

    if (_resizable) glfwSetWindowSizeCallback(getWindowHandle(), reinterpret_cast<GLFWwindowsizefun>(cbResize));

    glfwSetWindowUserPointer(getWindowHandle(), reinterpret_cast<void*>(this));
}

void Window::createResources(const Shader* _shader) {
    assert(mWindow != nullptr);

    mCamera = std::make_unique<Camera2D>();
    mFrameSprite = std::make_unique<Sprite>(std::make_unique<MBox2D>(2.0f, 2.0f), std::make_unique<Shader>(*_shader));

    createSizeDependendResource();
}

void Window::createSizeDependendResource() {
    mFrameBuffer.reset(new FrameBuffer(mWidth, mHeight));
    mFrameTexture.reset(new Tex2D_URGB(mFrameBuffer->getColorTexture(), mWidth, mHeight));
    mFrameBuffer->init();
    mFrameSprite->setTexture(0, mFrameTexture->getID());

    mCamera->setProjection(mWidth, mHeight);

    glViewport(0, 0, mWidth, mHeight);
}

void Window::evResize(int _width, int _height) {
    mWidth = _width;
    mHeight = _height;

    createSizeDependendResource();
    onResize();
}

void Window::renderToWindow() {
    glClearColor(mClearColor.r(), mClearColor.g(), mClearColor.b(), mClearColor.a());
    glClear(GL_COLOR_BUFFER_BIT);
    mFrameSprite->render(*(mCamera.get()), true);
}

// static methods 

void Window::cbResize(GLFWwindow* _window, int _width, int _height) {
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(_window));
    if (window == nullptr) return;

    window->evResize(_width, _height);
}