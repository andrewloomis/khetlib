#ifndef GAME_H
#define GAME_H

#include "piece.h"
#include <vector>
#include <memory>
#include <QList>
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    void startGame();
    void nextTurn() { currentTurn == Color::Grey ? currentTurn = Color::Red : currentTurn = Color::Grey; }
    bool isPieceAtPosition(Position pos);
    int possibleTranslationsForPiece(std::size_t index);
    const std::vector<std::shared_ptr<Piece>>& getPieces() const { return pieces; }
    void updatePiecePosition(std::size_t index, int x, int y);
    void updatePieceAngle(std::size_t index, int angle);
    QList<int> calculateBeamCoords(int startX, int startY);
    Color getPieceColor(std::size_t index) const;
    Color currentPlayerTurn() const { return currentTurn; }
//    bool isGodMode() const { return godMode; }
    bool operator==(const Game& otherGame);
//    std::shared_ptr<Piece> getPiece(size_t index) { return pieces[index]; }

signals:
    void pieceKilled(int index);

private:
    std::vector<std::shared_ptr<Piece>> pieces;
    Color currentTurn = Color::Grey;
//    bool godMode = false;

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
