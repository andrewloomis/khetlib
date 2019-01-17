#ifndef PIECE_H
#define PIECE_H

#include "khettypes.h"
#include <QString>
class Piece
{
public:
    Piece();
    Piece(int x, int y, int angle, Color color);
    virtual Interaction laserInteraction(Direction laserIncidentDir) const = 0;
    virtual bool canSwap() const { return false; }
    virtual bool canStack() const { return false; }
    virtual PieceType type() const = 0;
    Position position() const { return pos; }
    int angle() const { return mAngle; }
    int index() const { return mIndex; }
    void setIndex(int index) { mIndex = index; }
    void setPosition(int x, int y);
    void setAngle(int angle);
    virtual ~Piece() {}
private:
    Position pos;
    Color color;
    int mAngle;
    int mIndex;
};

#endif // PIECE_H
