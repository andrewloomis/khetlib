#ifndef GAME_H
#define GAME_H

#include "piece.h"
#include <array>

class Game
{
public:
    Game();
    void startGame();
    bool isPieceAtPosition(Position pos);
    int possibleTranslationsForPiece(const Piece& piece);

private:
    std::array<Piece, 80> pieces;

    struct Translations
    {
        static const int TopLeft = 1;
        static const int Top = 2;
        static const int TopRight = 4;
        static const int Left = 8;
        static const int Right = 16;
        static const int BottomLeft = 32;
        static const int Bottom = 64;
        static const int BottomRight = 128;
    };
};

#endif // GAME_H