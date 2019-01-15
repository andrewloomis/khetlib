#ifndef GAME_H
#define GAME_H

#include "piece.h"
#include <vector>
#include <memory>
#include <QList>

class Game
{
public:
    Game();
    void startGame();
    bool isPieceAtPosition(Position pos);
    int possibleTranslationsForPiece(std::size_t index);
    const std::vector<std::shared_ptr<Piece>>& getPieces() const { return pieces; }
    void updatePiecePosition(std::size_t index, int x, int y);
    void updatePieceAngle(std::size_t index, int angle);
    QList<int> calculateBeamCoords() const;

private:
    std::vector<std::shared_ptr<Piece>> pieces;

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
