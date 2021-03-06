#ifndef PYRAMID_H
#define PYRAMID_H

#include "piece.h"
#include "khettypes.h"

class Pyramid : public Piece
{
public:
    Pyramid(const Piece& piece)
        : Piece(piece) {}
    Pyramid(int x, int y, int angle, Color color)
        : Piece(x,y,angle,color) {}
    Interaction laserInteraction(Direction laserIncidentDir) const override;
    PieceType type() const override { return PieceType::Pyramid; }
    int value() const override { return 75000; }

private:
    bool debugInfo = false;
};

#endif
