#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "WindowUtils.hpp"

class Camera {
  private:
    glm::vec3 targetPos; // We need this stuff for pixel snapping
    glm::vec3 actualPos;

  public:
    Camera(glm::vec3 targetPos) : targetPos(targetPos) {}
};