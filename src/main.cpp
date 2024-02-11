#include "Camera.hpp"
#include "RenderPass.hpp"
#include "ShaderUtils.hpp"
#include "TextureUtils.hpp"
#include "WindowUtils.hpp"

int main(int argc, char **argv) {
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

    double time = 0.0;

    while (!glfwWindowShouldClose(window)) {
        time += 0.01;

        cameraPos = glm::vec3(0.0, 0.5f * sin(time), -0.5f * sin(time));

        texturePass.render();
        screenPass.render();

        // Swap the screen buffers + check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}