#version 330 core

#define WIDTH 480
#define HEIGHT 270

out vec4 FragColor;

in vec2 UV;

uniform sampler2D screenTexture;
uniform sampler2D depthTexture;

void main()
{
    float dx = 1.0 / WIDTH;
    float dy = 1.0 / HEIGHT;

    float depth = texture(depthTexture, UV / 2.0 + 0.5).r;
    float depthL = texture(depthTexture, UV / 2.0 + 0.5 - vec2(dx, 0)).r;
    float depthR = texture(depthTexture, UV / 2.0 + 0.5 + vec2(dx, 0)).r;
    float depthT = texture(depthTexture, UV / 2.0 + 0.5 + vec2(0, dy)).r;
    float depthB = texture(depthTexture, UV / 2.0 + 0.5 - vec2(0, dy)).r;

    float difference = max(depthL - depth, max(depthR - depth, max(depthT - depth, depthB - depth)));
    float outline = 1.0 + (difference > 0.01 ? 1.0 : 0.0);

    FragColor = vec4(outline * texture(screenTexture, UV / 2.0 + 0.5).xyz, 1.0);
}