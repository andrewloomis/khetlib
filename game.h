#ifndef GAME_H
#define GAME_H

#include "piece.h"
#include "khettypes.h"
#include <vector>
#include <memory>
#include <QList>
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    Game(Game& newGame);
    void startGame();
    void nextTurn() { currentTurn == Color::Grey ? currentTurn = Color::Red : currentTurn = Color::Grey; }
    bool isPieceAtPosition(Position pos);
    int possibleTranslationsForPiece(std::size_t index);

    const std::vector<std::shared_ptr<Piece>>& getPieces() const { return pieces; }

    void updatePiecePosition(std::size_t index, int x, int y);
    void updatePieceAngle(std::size_t index, int angle);

    QList<int> calculateBeamCoords(int startX, int startY);
    Color currentPlayerTurn() const { return currentTurn; }
    bool operator==(const Game& otherGame);

    Color getPieceColor(std::size_t index) const;
    Position getPiecePosition(size_t index) const { return pieces[index]->position(); }
    int getPieceAngle(size_t index) const { return pieces[index]->angle(); }
    PieceType getPieceType(size_t index) const { return pieces[index]->type(); }
    Move getLastMove() const { return lastMove; }
    void setLastMove(Move move) { lastMove = move; }

    void reset();

signals:
    void pieceKilled(int index);
    void pharoahKilled(int index);
    void unstackPiece(int index, QString color);

private:
    std::vector<std::shared_ptr<Piece>> pieces;
    Color currentTurn = Color::Grey;
    Move lastMove;
//    bool godMode = false;
};

#endif // GAME_H
