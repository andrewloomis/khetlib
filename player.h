#ifndef PLAYER_H
#define PLAYER_H

#include "khettypes.h"
#include <QString>

class Player
{
public:
    Player();
    Color pieceColor() const { return color; }
private:
    QString username;
    Color color;
};

#endif // PLAYER_H
