#ifndef OBELISK_H
#define OBELISK_H

#include "piece.h"
#include "khettypes.h"

class Obelisk : public Piece
{
public:
    Obelisk(int x, int y, int angle, Color color)
        : Piece(x,y,angle,color) { stack(); }
    Interaction laserInteraction(Direction laserIncidentDir) const override;
    bool canStack() const override { return true; }
    PieceType type() const override { return PieceType::Obelisk; }
    int value() const override { return isStacked() ? 25000 : 10000; }
};

#endif // OBELISK_H
