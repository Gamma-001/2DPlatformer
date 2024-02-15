#include <engine/texture.hpp>

#include <exception>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture()
:mWidth(0)
,mHeight(0)
,mChannels(0) {}

void Texture::loadFromFile(const std::filesystem::path& _path) {
    if (!std::filesystem::exists(_path)) throw std::invalid_argument("Invalid Path!");

    stbi_set_flip_vertically_on_load(true);
    unsigned char *rawData = stbi_load(reinterpret_cast<const char*>(_path.c_str()), &mWidth, &mHeight, &mChannels, 3);
    if (rawData == nullptr) throw std::invalid_argument(stbi_failure_reason());

    mData = std::vector<unsigned char> { rawData, rawData + mWidth * mHeight * mChannels };
    stbi_image_free(rawData);
}

void Texture::BindTexture() {
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mData.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

// void Texture::fromSolidColor(int _widht, int _height, int _channels = 3) {

// }