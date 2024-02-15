#include <engine/sprite.hpp>

Sprite::Sprite()
:mMesh(nullptr)
,mShader(nullptr) {}

Sprite::Sprite(std::unique_ptr <Mesh2D> _mesh, Shader* _shader)
:mMesh(std::move(_mesh))
,mShader(_shader) {}

void Sprite::render(const Camera2D& _camera) {
    if (!mShader || !mMesh) return;

    mShader->use();
    for (int i = 0; i < mTextures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, mTextures[i]);
        mShader->setInt("texture" + std::to_string(i), 0);
    }
    mMesh->render(*mShader, _camera, *this);
}

void Sprite::addTexture(GLuint _texture) {
    if (mTextures.size() >= 32) return;
    mTextures.push_back(_texture);
}