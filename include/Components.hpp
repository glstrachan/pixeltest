#pragma once

struct TargetPosition {
    float x, y, z;

    TargetPosition() : x(0), y(0), z(0) {}
    TargetPosition(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct ActualPosition {
    float x, y, z;

    ActualPosition() : x(0), y(0), z(0) {}
    ActualPosition(float x, float y, float z) : x(x), y(y), z(z) {}
};