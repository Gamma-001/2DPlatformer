#pragma once

#include <string>
#include <memory>

#include <glad/glad.h>

class Shader {
public:
    Shader();
    ~Shader();

    virtual void loadFromFile(const std::string& _pathVert, const std::string& _pathFrag);

    inline GLuint getID() const { return mShaderProgram; }
    inline void use() const { glUseProgram(mShaderProgram); }

    void setInt(const std::string& _name, int _val);

protected:
    void compileShader(GLuint shader, const char* shaderSource);

private:
    GLuint mShaderProgram;
};