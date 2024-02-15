#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <glad/glad.h>

class Texture {
public:
    Texture();
    // explicit Texture(std::vector <unsigned char> &&_data);

    void loadFromFile(const std::filesystem::path& _path);
    // void fromSolidColor(int _widht, int _height, int _channels = 3);

protected:
    void BindTexture();

private:
    int mWidth;
    int mHeight;
    int mChannels;

    std::vector<unsigned char> mData;
    GLuint mTexture;
};