#version 330 core
layout (location = 0) in vec3 position;

uniform vec3 cameraPos;

out vec3 FaceCoord;

void main() {
    mat4 rotationMatrix = mat4(1.0,  0.0,        0.0,         0.0,
                               0.0,  0.70710678, -0.70710678, 0.0,
                               0.0,  0.70710678, 0.70710678,  0.0,
                               0.0,  0.0,        0.0,         1.0);

    // Do world position scaling
    vec3 scaledPos = position * 0.5;

    // Scale based on aspect ratio
    vec3 ratioPos = scaledPos * vec3(480.0 / 640.0, 1.0, 1.0);

    // Do the camera translation
    vec3 translatedPos = ratioPos - cameraPos;

    // Rotate the camera
    vec4 transformedPos = rotationMatrix * vec4(translatedPos, 1.0);

    // Stretch the vertical axis to make faces square
    transformedPos.y *= 1.414213;

    // Set the face coordinate
    int faceId = gl_VertexID % 6;
    FaceCoord = vec3(((faceId) + 2) % 6 > 2 ? 1.0 : -1.0, ((faceId) + 1) % 6 > 2 ? 1.0 : -1.0, 0.0);
    
    gl_Position = transformedPos;
}