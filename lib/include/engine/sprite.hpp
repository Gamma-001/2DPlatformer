#pragma once

#include <memory>
#include <vector>

#include <glad/glad.h>

#include <gen/transform.hpp>
#include <engine/mesh.hpp>
#include <engine/shader.hpp>
#include <engine/camera.hpp>
#include <engine/texture.hpp>

class Sprite: public Transform2D {
public:
    Sprite();
    Sprite(std::unique_ptr<Mesh2D> _mesh, std::unique_ptr<Shader> _shader);

    void render(const Camera2D& _camera, bool _screenSpace = false);
    void setTexture(int _index, GLuint _texture);

    inline void setMesh(std::unique_ptr<Mesh2D> _mesh);
    inline void setShader(std::unique_ptr<Shader> _shader); 

private:
    std::unique_ptr<Mesh2D> mMesh;
    std::unique_ptr<Shader> mShader;
    std::vector<GLuint> mTextures;
};

void Sprite::setMesh(std::unique_ptr<Mesh2D> _mesh) {
    mMesh = std::move(_mesh);
}

void Sprite::setShader(std::unique_ptr<Shader> _shader) {
    mShader = std::move(_shader);
}