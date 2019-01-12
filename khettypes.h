#ifndef KHETTYPES_H
#define KHETTYPES_H

struct Position
{
    int x;
    int y;
    explicit Position(int x, int y)
        : x(x), y(y) {}
};

enum class Color
{
    Red = 0,
    Grey
};

enum class Interaction
{
    Hit = 0,
    ReflectNegX,
    ReflectPosX,
    ReflectNegY,
    ReflectPosY
};

enum class Direction
{
    NegX = 0,
    PosX,
    NegY,
    PosY
};

#endif