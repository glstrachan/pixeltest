#pragma once

#include "Components.hpp"
#include "WindowUtils.hpp"
#include <entt/entt.hpp>

class SnappingSystem {
  public:
    float time;

    SnappingSystem() : time(0) {}

    void update(entt::registry &registry, float deltaTime) {
        time += deltaTime;

        auto view = registry.view<TargetPosition, ActualPosition>();

        for (auto entity : view) {
            auto &target = view.get<TargetPosition>(entity);
            auto &actual = view.get<ActualPosition>(entity);

            target.x = sin(time) * 0.3;
            target.z = cos(time) * 0.3;

            // IMPORTANT: Use the same scaling factor as in the vertex shader
            actual.x = round(target.x * WIDTH * 0.5) / (WIDTH * 0.5);
            actual.z = round(target.z * HEIGHT * 0.5) / (HEIGHT * 0.5);
        }
    }
};