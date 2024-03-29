#pragma once

#include <filesystem>
#include <string>
#include <memory>

#include <glad/glad.h>

class Shader {
public:
    Shader();
    Shader(const Shader& _other);
    ~Shader();

    virtual void loadFromFile(const std::filesystem::path& _pathVert, const std::filesystem::path& _pathFrag);

    inline GLuint getID() const { return mShaderProgram; }
    inline void use() const;
    inline void discard() const;

    void setInt(const std::string& _name, int _val);

protected:
    void compileShader(GLuint shader, const char* shaderSource);
    
    bool isCopy; // in case the shader is created with a copy constructor, prevent calling any load with new shader

private:
    GLuint mShaderProgram;
};

inline void Shader::use() const {
    glUseProgram(mShaderProgram);
}

inline void Shader::discard() const {
    glUseProgram(0);
}