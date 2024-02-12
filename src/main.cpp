#include "RenderPass.hpp"
#include "ShaderUtils.hpp"
#include "TextureUtils.hpp"
#include "WindowUtils.hpp"

#include "Components.hpp"
#include "Systems.hpp"
#include <entt/entt.hpp>

int main(int argc, char **argv) {
    entt::registry registry;
    auto camera = registry.create();
    registry.emplace<TargetPosition>(camera);
    registry.emplace<ActualPosition>(camera);
    SnappingSystem snappingSystem;

    // Window setup
    GLFWwindow *window = setupWindow();

    // Set up data to for render passes
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    GLuint screenFBO;
    glGenFramebuffers(1, &screenFBO);

    // Set up render passes
    TexturePass texturePass(screenFBO, cameraPos);
    texturePass.setup();

    ScreenPass screenPass(screenFBO, window);
    screenPass.setup();

    while (!glfwWindowShouldClose(window)) {
        snappingSystem.update(registry, 0.001f);
        auto actual = registry.get<ActualPosition>(camera);
        cameraPos = glm::vec3(actual.x, actual.y, actual.z);

        texturePass.render();
        screenPass.render();

        // Swap the screen buffers + check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    registry.destroy(camera);
    glfwTerminate();

    return 0;
}