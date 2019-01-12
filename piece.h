#ifndef PIECE_H
#define PIECE_H

#include "khettypes.h"

class Piece
{
public:
    Piece();
    Piece(int x, int y, int angle, Color color);
    virtual Interaction laserInteraction(Direction laserIncidentDir);
    Position position() const { return pos; }

private:
    Position pos;
    Color color;
    int angle;
};

#endif // PIECE_H
