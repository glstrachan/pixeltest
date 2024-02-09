#version 330 core
out vec4 FragColor;

in vec3 FaceCoord;

uniform sampler2D dirtTexture;

void main() {
    FragColor = texture(dirtTexture, FaceCoord.xy / 2.0 + 0.5);
}