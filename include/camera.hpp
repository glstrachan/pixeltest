#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Camera {
public:
    enum Mode {
        Perspective,
        Orthographic
    };

    Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, Mode mode = Perspective);
    Camera(const glm::vec3& position, const glm::vec3& direction, float distance, const glm::vec3& up, Mode mode = Perspective);

    void setPosition(const glm::vec3& newPosition);
    void setTarget(const glm::vec3& newTarget);
    void setUp(const glm::vec3& newUp);
    void setMode(Mode newMode);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float width, float height) const;

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    Mode mode;
};