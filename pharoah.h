#ifndef PHAROAH_H
#define PHAROAH_H

#include "piece.h"
#include "khettypes.h"

class Pharoah : public Piece
{
public:
    Pharoah(int x, int y, int angle, Color color)
        : Piece(x,y,angle,color) {}
    Interaction laserInteraction(Direction laserIncidentDir) const override;
    PieceType type() const override { return PieceType::Pharoah; }
};

#endif // PHAROAH_H
