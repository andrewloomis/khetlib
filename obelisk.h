#ifndef OBELISK_H
#define OBELISK_H

#include "piece.h"
#include "khettypes.h"

class Obelisk : public Piece
{
public:
    Obelisk(int x, int y, int angle, Color color)
        : Piece(x,y,angle,color) {}
    Interaction laserInteraction(Direction laserIncidentDir) const override;
    bool canStack() const override { return true; }
};

#endif // OBELISK_H
