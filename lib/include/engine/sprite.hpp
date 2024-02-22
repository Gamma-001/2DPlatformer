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
    Sprite(std::unique_ptr <Mesh2D> _mesh, Shader* _shader);

    void render(const Camera2D& _camera, bool _screenSpace = false);
    void addTexture(GLuint _texture);

private:
    std::unique_ptr<Mesh2D> mMesh;
    std::vector<GLuint> mTextures;
    Shader* mShader;
};