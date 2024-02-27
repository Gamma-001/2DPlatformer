#pragma once

#include <memory>

#include <gui/window.hpp>
#include <engine/texture.hpp>

class MainWindow: public Window {
public:
    MainWindow(int _width, int _height);

    virtual void init() override;
    virtual void renderLoop(float _deltaTime) override;

private:
    virtual void onResize() override;

    Sprite mCharacter;
    std::unique_ptr<Tex2D_URGB> mCharacterTex; // TOOD: create a texture atlas
};