#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <gen/transform.hpp>
#include <engine/shader.hpp>
#include <engine/camera.hpp>

class Mesh2D {
public:
    Mesh2D(GLuint _nVerts = 0, GLuint _nIndices = 0);
    ~Mesh2D();

    virtual void render(const Shader& _shader, const Camera2D& _camera, Transform2D& _transform);

protected:
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    bool setBuffers(GLenum _usage = GL_STATIC_DRAW);

    void pushVertex(GLfloat _x, GLfloat _y, GLfloat _z);
    void pushTriangle(GLuint _a, GLuint _b, GLuint _c);
    void setUV(int _index, GLfloat _x, GLfloat _y);

    // initial mesh loading / calculation
    virtual void initVerts() = 0;
};

class MBox2D: public Mesh2D {
public:
    MBox2D(GLfloat _width = 1.0f, GLfloat _height = 1.0f);

protected:
    void initVerts() override;

private:
    GLfloat height, width;
};