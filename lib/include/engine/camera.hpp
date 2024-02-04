#pragma once

#include <glm/glm.hpp>

enum class cameraDirection { front, right, up };

class Camera2D {
public:
    enum class PROJECTION {
        ORTHOGRAPHIC
    };

    Camera2D(glm::vec2 _position = glm::vec2(0.0f, 0.0f), float _rotation = 0.0f);

    inline const glm::mat4& getProjectionMat() const { return mMatProjection; }
    inline const glm::mat4& getViewMat() const { return mMatView; }

    void setProjection(float _width, float _height, float _near = 0.1f, float _far = 1000.0f, PROJECTION _projection = PROJECTION::ORTHOGRAPHIC);
    void translate(glm::vec2 _offset);
    void rotate(float _offset);
    void setScale(float _zoom);

private:
    void recalculateViewMat();

    glm::vec3 mPosition;
    float mRotation;
    float mScale;

	glm::mat4 mMatView;
	glm::mat4 mMatProjection;
};