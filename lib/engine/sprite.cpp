#include <engine/sprite.hpp>

Sprite::Sprite()
:mMesh(nullptr)
,mShader(nullptr) {
    mTextures.reserve(8);
}

Sprite::Sprite(std::unique_ptr<Mesh2D> _mesh, std::unique_ptr<Shader> _shader)
:mMesh(std::move(_mesh))
,mShader(std::move(_shader)) {
    mTextures.reserve(8);
}

void Sprite::render(const Camera2D& _camera, bool _screenSpace) {
    if (!mShader || !mMesh) return;

    mShader->use();
    for (int i = 0; i < mTextures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, mTextures[i]);
        mShader->setInt("texture" + std::to_string(i), 0);
    }
    mMesh->render(*mShader, _camera, *this, _screenSpace);
    mShader->discard();
}

void Sprite::setTexture(int _index, GLuint _texture) {
    assert(mShader != nullptr);

    if (_index >= 0 && _index < 32) {
        if (_index >= mTextures.size()) mTextures.resize(_index + 1);
        mTextures[_index] = _texture;
    }
}