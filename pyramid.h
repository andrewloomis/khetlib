#ifndef PYRAMID_H
#define PYRAMID_H

#include "piece.h"
#include "khettypes.h"

class Pyramid : public Piece
{
public:
    Pyramid(int x, int y, int angle, Color color)
        : Piece(x,y,angle,color) {}
    Interaction laserInteraction(Direction laserIncidentDir) override;
//    ~Pyramid() {}
};

#endif
