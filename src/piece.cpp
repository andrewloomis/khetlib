#include "piece.h"

Piece::Piece() : pos(0,0) {}

Piece::Piece(int x, int y, int angle, Color color)
    : pos(x,y), color(color), mAngle(angle)
{
    
}

Interaction Piece::laserInteraction(Direction laserIncidentDir) const {}

void Piece::setPosition(int x, int y, int angle)
{
    pos.x = x;
    pos.y = y;
    mAngle = angle;
}
