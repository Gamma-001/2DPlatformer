#include <gen/transform.hpp>

#include <cmath>

#include <glm/ext/matrix_transform.hpp>

glm::vec3 Transform2D::up = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Transform2D::right = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Transform2D::forward = glm::vec3(0.0f, 1.0f, 0.0f);

Transform2D::Transform2D(glm::vec2 _position, float _rotation, float _scale)
:mPosition(glm::vec3(_position.x, _position.y, 0.0f))
,mScale(_scale) {
    mMatRot = glm::rotate(glm::mat4(1.0f), _rotation, Transform2D::up);
    recalculateRotation();
}

glm::mat4 Transform2D::getMatrix() const {
    glm::mat4 res = glm::translate(glm::mat4(1.0f), mPosition);
    res = res * mMatRot;
    res = glm::scale(res, glm::vec3(mScale));

    return res;
}

void Transform2D::translate(const glm::vec3& _offset) {
    mPosition += _offset;
}

void Transform2D::setPosition(const glm::vec3& _position) {
    mPosition = _position;
}

void Transform2D::translateLocal(const glm::vec3& _axis, float _offset) {
    glm::vec3 localAxis = mMatRot * glm::vec4(_axis, 1.0f);
    mPosition += localAxis * _offset;
}
 
void Transform2D::rotate(float _offset) {
    mMatRot = glm::rotate(mMatRot, _offset, Transform2D::up);
    recalculateRotation();
}

void Transform2D::rotate3D(const glm::vec3& _offset) {
    float factor = glm::length(_offset);
    glm::vec3 offsetNorm = glm::normalize(_offset);
    mMatRot = glm::rotate(mMatRot, factor, offsetNorm);
    recalculateRotation();
}

void Transform2D::setScale(float _scale) {
    mScale = _scale;
}

void Transform2D::recalculateRotation() {
    // https://nghiaho.com/?page_id=846
    
    mRotation.x = atan2(mMatRot[3][2], mMatRot[3][3]);
    mRotation.y = atan2(-mMatRot[3][1], glm::length(glm::vec2(mMatRot[3][2], mMatRot[3][3])));
    mRotation.z = atan2(mMatRot[2][1], mMatRot[1][1]);
}