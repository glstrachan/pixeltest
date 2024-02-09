#include "Camera.hpp"

Camera::Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, Mode mode)
    : position(position), target(target), up(glm::normalize(up)), mode(mode) {
}

Camera::Camera(const glm::vec3& position, const glm::vec3& direction, float distance, const glm::vec3& up, Mode mode)
    : position(position), up(glm::normalize(up)), mode(mode) {
    target = position + glm::normalize(direction) * distance;
}

void Camera::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
}

void Camera::setTarget(const glm::vec3& newTarget) {
    target = newTarget;
}

void Camera::setUp(const glm::vec3& newUp) {
    up = glm::normalize(newUp);
}

void Camera::setMode(Mode newMode) {
    mode = newMode;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix(float width, float height) const {
    if (mode == Perspective) {
        return glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
    } else {
        float orthoWidth = width / 100.0f;
        float orthoHeight = height / 100.0f;
        return glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -100.0f, 100.0f);
    }
}
