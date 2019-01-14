#ifndef KHETTYPES_H
#define KHETTYPES_H

struct Position
{
    int x;
    int y;
    Position(int x, int y)
        : x(x), y(y) {}
};

enum class Color
{
    Red = 0,
    Grey
};

enum class Interaction
{
    Kill = 0,
    ReflectNegX,
    ReflectPosX,
    ReflectNegY,
    ReflectPosY,
    Error
};

enum class Direction
{
    NegX = 0,
    PosX,
    NegY,
    PosY
};

#endif
