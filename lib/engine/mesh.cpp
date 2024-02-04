#include <engine/mesh.hpp>

#include <glm/gtc/type_ptr.hpp>

// ---------- Mesh

Mesh2D::Mesh2D(GLuint _nVerts, GLuint _nIndices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    if (_nVerts) vertices.reserve(_nVerts * 3);
    if (_nIndices) indices.reserve(_nIndices * 3);
}

Mesh2D::~Mesh2D() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool Mesh2D::setBuffers(GLenum _usage) {
    if (vertices.size() < 3 || indices.size() < 3) return false;

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), _usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), _usage);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Mesh2D::pushVertex(GLfloat _x, GLfloat _y, GLfloat _z) {
    vertices.push_back(_x);
    vertices.push_back(_y);
    vertices.push_back(_z);
}

void Mesh2D::pushTriangle(GLuint _a, GLuint _b, GLuint _c) {
    indices.push_back(_a);
    indices.push_back(_b);
    indices.push_back(_c);
}

void Mesh2D::render(const Shader& _shader, const Camera2D& _camera) {
    glUseProgram(_shader.getShader());

    GLuint locProj = glGetUniformLocation(_shader.getShader(), "projection");
    GLuint locView = glGetUniformLocation(_shader.getShader(), "view");
    GLuint locModel = glGetUniformLocation(_shader.getShader(), "model");

    if (locProj != -1) glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(_camera.getProjectionMat()));
    if (locView != -1) glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(_camera.getViewMat()));
    if (locModel != -1) glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(getMatrix()));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glUseProgram(0);
}

// ---------- MBox2D

MBox2D::MBox2D(GLfloat _width, GLfloat _height)
:Mesh2D(4, 2)
,width(_width)
,height(_height) {
    initVerts();
}

void MBox2D::initVerts() {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;

    // top-left to bottom-right
    for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
            pushVertex(j * halfWidth, i * halfHeight, 0.0f);
        }
    }
    pushTriangle(0, 1, 2);
    pushTriangle(1, 3, 2);

    setBuffers();
}