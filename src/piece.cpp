#include "piece.h"

Piece::Piece() : pos(0,0) {}

Piece::Piece(int x, int y, int angle, Color color)
    : pos(x,y), mColor(color), mAngle(angle)
{
    
}

bool Piece::operator==(const Piece &otherPiece)
{
    return (type() == otherPiece.type() &&
            position() == otherPiece.position() &&
            angle() == otherPiece.angle() &&
            color() == otherPiece.color() &&
            index() == otherPiece.index() &&
            isKilled() == otherPiece.isKilled());
}

void Piece::setPosition(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void Piece::setPosition(Position position)
{
    pos.x = position.x;
    pos.y = position.y;
}

void Piece::setAngle(int angle)
{
    mAngle = angle;
}
