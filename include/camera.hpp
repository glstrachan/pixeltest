#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Camera {
public:
    enum Mode {
        Perspective,
        Orthographic
    };

    Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, Mode mode = Perspective)
        : position(position), target(target), up(glm::normalize(up)), mode(mode) {
    }

    Camera(const glm::vec3& position, const glm::vec3& direction, float distance, const glm::vec3& up, Mode mode = Perspective)
        : position(position), up(glm::normalize(up)), mode(mode) {
        target = position + glm::normalize(direction) * distance;
    }

    void setPosition(const glm::vec3& newPosition) {
        position = newPosition;
    }

    void setTarget(const glm::vec3& newTarget) {
        target = newTarget;
    }

    void setUp(const glm::vec3& newUp) {
        up = glm::normalize(newUp);
    }

    void setMode(Mode newMode) {
        mode = newMode;
    }

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, target, up);
    }

    glm::mat4 getProjectionMatrix(float width, float height) const {
        if (mode == Perspective) {
            return glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
        } else {
            float orthoWidth = width / 100.0f;
            float orthoHeight = height / 100.0f;
            return glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -100.0f, 100.0f);
        }
    }

private:
    glm::vec3 position;
    glm::vec3 target; // Using target instead of direction
    glm::vec3 up;
    Mode mode;
};
