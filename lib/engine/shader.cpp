#include <engine/shader.hpp>

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <memory>

Shader::Shader() {
    shaderProgram = glCreateProgram();
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::loadFromFile(const std::string& _pathVert, const std::string& _pathFrag) {
    if (!_pathVert.size() || !_pathFrag.size()) throw std::invalid_argument("source paths cannot be empty");

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::ifstream vertSource;
    std::ifstream fragSource;
    std::string vertStr;
    std::string fragStr;

    // ensure ifstream objects can throw error
    vertSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        std::stringstream ssVert;
        std::stringstream ssFrag;
        
        vertSource.open(_pathVert.c_str());
        fragSource.open(_pathFrag.c_str());
        ssVert << vertSource.rdbuf();
        ssFrag << fragSource.rdbuf();
        vertSource.close();
        fragSource.close();

        vertStr = ssVert.str();
        fragStr = ssFrag.str();
    }
    catch(std::ifstream::failure &e) {
        std::cout << "ERROR_SHADER_READ\n" << e.what() << '\n';
    }

    compileShader(vertShader, vertStr.c_str());
    compileShader(fragShader, fragStr.c_str());

    // link the shaders
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    {
        GLint success;
        GLchar infoLog[512];

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cout << "ERROR_SHADER_LINK\n" << infoLog << '\n';
        }
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

void Shader::compileShader(GLuint shader, const char* shaderSource) {
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    {
        GLint success;
        GLchar infoLog[512];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "ERROR_SHADER_COMPILE\n" << infoLog << '\n';
        }
    }
}