#include <engine/camera.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

Camera2D::Camera2D(glm::vec2 _position, float _rotation)
:mPosition(glm::vec3(_position.x, _position.y, -10.0f))
,mRotation(_rotation)
,mScale(1.0f)
,mMatView(glm::mat4(1.0f))
,mMatProjection(glm::mat4(1.0f)) {
    recalculateViewMat();
}

void Camera2D::setProjection(float _width, float _height, float _near, float _far, PROJECTION _projection) {
    switch (_projection) {
    case PROJECTION::ORTHOGRAPHIC: {
        float aspect = _width / _height;
        mMatProjection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, _near, _far);
        break;
    }

    default:
        mMatProjection = glm::mat4(1.0f);
        break;
    }
}

void Camera2D::recalculateViewMat() {
    mMatView = glm::translate(glm::mat4(1.0f), mPosition);
    mMatView = glm::rotate(mMatView, mRotation, glm::vec3(0.0f, 0.0f, 1.0f));
    mMatView = glm::scale(mMatView, glm::vec3(mScale));
}

void Camera2D::translate(glm::vec2 _offset) {
    mPosition -= glm::vec3(_offset, 0.0f);    
    recalculateViewMat();
}

void Camera2D::rotate(float _offset) {
    mRotation -= _offset;
    recalculateViewMat();
}

void Camera2D::setScale(float _zoom) {
    if (_zoom == 0.0f) return;

    mScale = 1.0f / _zoom;
    recalculateViewMat();
}