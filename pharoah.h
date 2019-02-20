#ifndef PHAROAH_H
#define PHAROAH_H

#include "piece.h"
#include "khettypes.h"

class Pharoah : public Piece
{
public:
    Pharoah(const Piece& piece)
        : Piece(piece) {}
    Pharoah(int x, int y, int angle, Color color)
        : Piece(x,y,angle,color) {}
    Interaction laserInteraction(Direction laserIncidentDir) const override;
    PieceType type() const override { return PieceType::Pharoah; }
    int value() const override { return 10000000; }
};

#endif // PHAROAH_H
