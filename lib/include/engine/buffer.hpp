#pragma once

#include <glad/glad.h>

class FrameBuffer {
public:
    FrameBuffer();
    FrameBuffer(GLsizei _width, GLsizei _height);
    ~FrameBuffer();

    inline const GLuint getColorTexture() const { return mTexColor; }
    inline const GLsizei getWidth() const { return mWidth; }
    inline const GLsizei getHeight() const { return mHeight; }

    void resize(int _width, int _height);

    void init();
    void use(bool _depthTest = true);
    void discard();

private:
    GLuint mFBO, mTexColor, mRBO;
    GLsizei mWidth, mHeight;
};