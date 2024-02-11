#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D screenTexture;
uniform sampler2D depthTexture;


void main()
{
    FragColor = vec4(vec3(texture(depthTexture, UV / 2.0 + 0.5).r), 1.0);
}