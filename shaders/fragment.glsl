#version 330 core
out vec4 FragColor;

in vec3 FaceCoord;

void main() {
    FragColor = vec4(FaceCoord, 1.0);
}