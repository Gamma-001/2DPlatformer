#pragma once

#include <string>
#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <gen/color.hpp>
#include <engine/buffer.hpp>
#include <engine/texture.hpp>
#include <engine/sprite.hpp>
#include <engine/camera.hpp>

class Window {
public:
    Window(int _width, int _height);
    ~Window();

    GLFWwindow* getWindowHandle() const { return mWindow; }
    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }

    void createWindow(const std::string& _title, bool _resizable = true);
    // size independent resources
    void createResources(const Shader* _shader);
    void createSizeDependendResource();

    void evResize(int _width, int _height);

    static void cbResize(GLFWwindow* _window, int _width, int _height);

protected:
    virtual void init() = 0;
    virtual void render(float _deltaTime) = 0;
    virtual void onResize() = 0;

    virtual void renderToWindow();

    std::unique_ptr<FrameBuffer>    mFrameBuffer;
    std::unique_ptr<Tex2D_URGB>     mFrameTexture;
    std::unique_ptr<Sprite>         mFrameSprite;
    std::unique_ptr<Camera2D>       mCamera;
    Color_FRGBA mClearColor;
    
private:
    GLFWwindow* mWindow;
    int         mWidth;
    int         mHeight;
};