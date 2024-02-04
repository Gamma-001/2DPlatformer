#pragma once

#include <glm/glm.hpp>

/**
 * only use a matrix for rotation
 * all transforms are only applied when retrieving the full transformation matrix
 * the final transformation would be the result of scale + rotation at origin + translate
 */
class Transform2D {
public:
    Transform2D(glm::vec2 _position = glm::vec2(0.0f, 0.0f), float _rotation = 0.0f, float _scale = 1.0f);

    inline const glm::vec3& getPosition() const { return mPosition; }
    inline const glm::vec3& getRotation() const { return mRotation; }
    inline float getScale() const { return mScale; }
    glm::mat4 getMatrix() const;

    void translate(const glm::vec3& _offset);
    void setPosition(const glm::vec3& _position);
    void translateLocal(const glm::vec3& _axis, float _offset);
    void rotate(float _offset);
    void rotate3D(const glm::vec3& _offset);
    void setScale(float _scale);

    static glm::vec3 up;
    static glm::vec3 right;
    static glm::vec3 forward;

private:
    void recalculateRotation();

    glm::mat4 mMatRot;
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    float mScale;
};