#ifndef KHETTYPES_H
#define KHETTYPES_H

struct Position
{
    int x;
    int y;
    Position() {}
    Position(int x, int y)
        : x(x), y(y) {}
    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Position& other) const
    {
        return !(operator==(other));
    }
};

enum class PieceType
{
    Pyramid = 0,
    Djed,
    Obelisk,
    Pharoah
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

struct Translations
{
    static const int TopLeft = 1;
    static const int Top = 2;
    static const int TopRight = 4;
    static const int Left = 8;
    static const int Right = 16;
    static const int BottomLeft = 32;
    static const int Bottom = 64;
    static const int BottomRight = 128;
};

struct Move
{
    Move() {}
    Move(int index, Position pos, int angle = -1)
        : pieceIndex(index), movedPosition(pos),
          movedAngle(angle) {}
    static Move minInit();
    static Move maxInit();
    bool operator>(const Move& other)
    {
        return value > other.value;
    }
    bool operator<(const Move& other)
    {
        return value < other.value;
    }
    bool operator>=(const Move& other)
    {
        return value >= other.value;
    }
    bool operator<=(const Move& other)
    {
        return value <= other.value;
    }

    int pieceIndex;
    Position movedPosition;
    int movedAngle;
    int value = 0;
};

#endif
