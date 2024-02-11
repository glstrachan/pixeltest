#pragma once

#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/vec3.hpp>

#include "WindowUtils.hpp"
#include "ShaderUtils.hpp"
#include "TextureUtils.hpp"

class RenderPass {
  public:
    virtual ~RenderPass() = default;

    virtual void setup() = 0;  // Prepare the render pass
    virtual void render() = 0; // Execute the render pass
};

class TexturePass : public RenderPass {
  private:
    GLuint shaderProgram;
    GLuint texture;
    GLuint VAO, VBO, FBO;

    GLfloat vertices[18] = {
        -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f,
        0.0f,  0.0f,  0.0f, 0.0f, -0.0f, 0.0f, -0.0f, 0.0f, 0.0f,
    };

    const glm::vec3 &cameraPos;

  public:
    TexturePass(GLuint FBO, const glm::vec3 &cameraPos) : FBO(FBO), cameraPos(cameraPos) {}

    void setup() override {
        shaderProgram = createProgram("shaders/cubeVertex.glsl", "shaders/cubeFragment.glsl");
        texture = loadTextureFromFile("assets/textures/dirt.png");
        glBindTexture(GL_TEXTURE_2D, texture);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void render() override {
      glBindFramebuffer(GL_FRAMEBUFFER, FBO);
      glViewport(0, 0, WIDTH, HEIGHT);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glUseProgram(shaderProgram);

      GLuint cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
      glUniform3f(cameraPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture);

      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);
    }

    ~TexturePass() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
        glDeleteTextures(1, &texture);
    }
};

class ScreenPass : public RenderPass {
  private:
    GLuint shaderProgram;
    GLuint colorTexture, depthTexture;
    GLuint VAO, VBO, FBO;

    GLFWwindow *window;
    int framebufferWidth, framebufferHeight;

    GLfloat vertices[18] = {
        -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  0.0f, 1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    };

  public:
    ScreenPass(GLuint FBO, GLFWwindow *window) : FBO(FBO), window(window) {}

    void setup() override {
        shaderProgram = createProgram("shaders/screenVertex.glsl", "shaders/screenFragment.glsl");

        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Important that we bind the FBO before creating the textures
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        glGenTextures(1, &colorTexture);
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WIDTH, HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void render() override {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, framebufferWidth, framebufferHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glUniform1i(glGetUniformLocation(shaderProgram, "screenTexture"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glUniform1i(glGetUniformLocation(shaderProgram, "depthTexture"), 1);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    ~ScreenPass() {
        glDeleteFramebuffers(1, &FBO);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
        glDeleteTextures(1, &colorTexture);
        glDeleteTextures(1, &depthTexture);
    }
};