#pragma once

#include <string>

#include <glad/glad.h>

class Shader {
public:
    Shader();
    ~Shader();

    virtual void loadFromFile(const std::string& _pathVert, const std::string& _pathFrag);

    inline GLuint getShader() const { return shaderProgram; }

protected:
    void compileShader(GLuint shader, const char* shaderSource);

private:
    GLuint shaderProgram;
};