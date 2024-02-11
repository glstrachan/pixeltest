#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D screenTexture;
uniform sampler2D depthTexture;


void main()
{
    FragColor = texture(screenTexture, UV / 2.0 + 0.5);
}