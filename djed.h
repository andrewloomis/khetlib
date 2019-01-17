#ifndef DJED_H
#define DJED_H

#include "piece.h"
#include "khettypes.h"

class Djed : public Piece
{
public:
    Djed(int x, int y, int angle, Color color)
        : Piece(x,y,angle,color) {}
    Interaction laserInteraction(Direction laserIncidentDir) const override;
    bool canSwap() const override { return true; }
    PieceType type() const override { return PieceType::Djed; }
};

#endif // DJED_H