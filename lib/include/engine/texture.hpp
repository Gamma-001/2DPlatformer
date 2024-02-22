#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <filesystem>
#include <exception>
#include <type_traits>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <gen/color.hpp>

template <class T>
class Texture2DRef {
public:
    Texture2DRef();
    explicit Texture2DRef(GLuint _texture);
    ~Texture2DRef();

    inline const GLuint getID() const { return mTexture; }

protected:
    virtual void bindTexture() = 0;

    int mWidth;
    int mHeight;
    std::vector<T> mData;
    GLuint mTexture;
};

template <class T>
Texture2DRef<T>::Texture2DRef()
:mWidth(0)
,mHeight(0) {
    glGenTextures(1, &mTexture);
}

template <class T>
Texture2DRef<T>::Texture2DRef(GLuint _texture)
:mWidth(0)
,mHeight(0),
mTexture(_texture) {}

template <class T>
Texture2DRef<T>::~Texture2DRef() {
    glDeleteTextures(1, &mTexture);
}


template <class T, int TChannel>
class Texture2D: public Texture2DRef<T> {
public:
    Texture2D();
    Texture2D(GLuint _texture, int _width, int _height);

    void loadFromFile(const std::filesystem::path& _path);
    void fromSolidColor(int _width, int _height, Color<T, TChannel> _color);

protected:
    void bindTexture() override;

private:
    typedef Texture2DRef<T> super;
};

template <class T, int TChannel>
Texture2D<T, TChannel>::Texture2D(): Texture2DRef<T>() {}

template <class T, int TChannel>
Texture2D<T, TChannel>::Texture2D(GLuint _texture, int _width, int _height)
:Texture2DRef<T>(_texture) {
    super::mWidth = _width;
    super::mHeight = _height;
}

template <class T, int TChannel>
void Texture2D<T, TChannel>::loadFromFile(const std::filesystem::path& _path) {
    if (!std::filesystem::exists(_path)) throw std::invalid_argument("Invalid Path!");

    stbi_set_flip_vertically_on_load(true);
    unsigned char *rawData = stbi_load(_path.string().c_str(), &(super::mWidth), &(super::mHeight), nullptr, TChannel);
    if (rawData == nullptr) throw std::invalid_argument(stbi_failure_reason());

    super::mData = std::vector<T> { rawData, rawData + super::mWidth * super::mHeight * TChannel };
    stbi_image_free(rawData);

    bindTexture();
}

template <class T,int TChannel>
void Texture2D<T, TChannel>::fromSolidColor(int _width, int _height, Color<T, TChannel> _color) {
    super::mWidth = _width;
    super::mHeight = _height;

    super::mData.erase();
    super::mData.reserve(_width * _height * TChannel);
    for (int i = 0; i < _width * _height; i++) {
        for (int j = 0; j < TChannel; j++) {
            super::mData.push_back(_color.getIndex(j));
        }
    }

    bindTexture();
}

template <class T, int TChannel>
void Texture2D<T, TChannel>::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, super::mTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, super::mWidth, super::mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, super::mData.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

typedef Texture2D<uint8_t, 3>   Tex2D_URGB;
typedef Texture2D<uint8_t, 4>   TexD_URGBA;