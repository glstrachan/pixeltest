#version 330 core
layout (location = 0) in vec2 position;

out vec2 UV;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    UV = position;
}