#include "ShaderUtils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

std::string loadShaderCode(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to load shader: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

GLuint compileShader(GLenum type, const std::string &code) {
    GLuint shader = glCreateShader(type);
    const char *codeCStr = code.c_str();
    glShaderSource(shader, 1, &codeCStr, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::string shaderType = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        std::cerr << "ERROR::" << shaderType << "_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}

GLuint createProgram(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string vertCode = loadShaderCode(vertexPath);
    std::string fragCode = loadShaderCode(fragmentPath);

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragCode);

    if (vertexShader == 0 || fragmentShader == 0)
        return 0;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER_PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}