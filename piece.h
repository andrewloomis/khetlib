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
    void stack() { stacked = true; }
    void unstack() { stacked = false; }
    Position position() const { return pos; }
    int angle() const { return mAngle; }
    int index() const { return mIndex; }
    void setIndex(int index) { mIndex = index; }
    void setPosition(int x, int y);
    void setAngle(int angle);
    bool isKilled() const { return killed; }
    void setKilled() { killed = true; }
    Color color() const { return mColor; }
    virtual ~Piece() {}
    bool operator==(const Piece& otherPiece);
    bool operator!=(const Piece& otherPiece) { return !operator==(otherPiece); }

private:
    Position pos;
    Color mColor;
    int mAngle;
    int mIndex;
    bool stacked = false;
    bool killed = false;
};

#endif // PIECE_H
