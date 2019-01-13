#include "piece.h"

Piece::Piece() : pos(0,0) {}

Piece::Piece(int x, int y, int angle, Color color)
    : pos(x,y), angle(angle), color(color)
{
    
}

Interaction Piece::laserInteraction(Direction laserIncidentDir) {}
//Piece::~Piece()
//{

//}
