#ifndef PIECE_H
#define PIECE_H

#include "khettypes.h"

class Piece
{
public:
    Piece();
    Piece(int x, int y, int angle, Color color);
    virtual Interaction laserInteraction(Direction laserIncidentDir) const;
    Position position() const { return pos; }
    int angle() const { return mAngle; }
    void setPosition(int x, int y, int angle);
    virtual ~Piece() {}
private:
    Position pos;
    Color color;
    int mAngle;
};

#endif // PIECE_H
