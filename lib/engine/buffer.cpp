#include <engine/buffer.hpp>

#include <stdexcept>

FrameBuffer::FrameBuffer()
:mWidth(0)
,mHeight(0) {}

FrameBuffer::FrameBuffer(GLsizei _width, GLsizei _height)
:mWidth(_width)
,mHeight(_height) {
    glGenFramebuffers(1, &mFBO);
    glGenTextures(1, &mTexColor);
    glGenRenderbuffers(1, &mRBO);
}

void FrameBuffer::init() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

    glBindTexture(GL_TEXTURE_2D, mTexColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexColor, 0);

    // render buffer for depth and stencil attachment 
    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
    glFramebufferRenderbuffer(GL_RENDERBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Framebuffer is not complete");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::use(bool _depthTest) {
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    if (_depthTest) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);
}

void FrameBuffer::discard() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &mFBO);
    glDeleteRenderbuffers(1, &mRBO);
}