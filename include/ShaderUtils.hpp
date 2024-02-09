#pragma once

#include <GL/glew.h>
#include <string>

// Loads shader code from a file.
std::string loadShaderCode(const std::string& path);

// Compiles a shader from provided code.
GLuint compileShader(GLenum type, const std::string& code);

// Links vertex and fragment shaders into a shader program.
GLuint createProgram(const std::string& vertexPath, const std::string& fragmentPath);