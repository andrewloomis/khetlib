#include "game.h"
#include "pyramid.h"
#include "djed.h"
#include "obelisk.h"
#include "pharoah.h"
#include <QDebug>
#include <QTimer>

Game::Game()
{
    startGame();
}

Game::Game(const Game& newGame)
    : currentTurn(newGame.currentTurn),
      lastMove(newGame.lastMove), gameOver(newGame.gameOver),
      debugInfo(newGame.debugInfo)
{
    for (const auto& piece : newGame.pieces)
    {
        switch(piece->type())
        {
        case PieceType::Pyramid:
            pieces.push_back(std::make_unique<Pyramid>(*piece));
            break;
        case PieceType::Obelisk:
            pieces.push_back(std::make_unique<Obelisk>(*piece));
            break;
        case PieceType::Djed:
            pieces.push_back(std::make_unique<Djed>(*piece));
            break;
        case PieceType::Pharoah:
            pieces.push_back(std::make_unique<Pharoah>(*piece));
            break;
        }
    }
//    qDebug() << "copy";
}

void Game::startGame()
{
    pieces.push_back(std::make_unique<Pyramid>(7,0,270,Color::Red));
    pieces.push_back(std::make_unique<Pyramid>(2,1,0,Color::Red));
    pieces.push_back(std::make_unique<Pyramid>(0,3,180,Color::Red));
    pieces.push_back(std::make_unique<Pyramid>(0,4,270,Color::Red));
    pieces.push_back(std::make_unique<Pyramid>(6,5,270,Color::Red));
    pieces.push_back(std::make_unique<Pyramid>(7,3,270,Color::Red));
    pieces.push_back(std::make_unique<Pyramid>(7,4,180,Color::Red));
    pieces.push_back(std::make_unique<Obelisk>(6,0,0,Color::Red));
    pieces.push_back(std::make_unique<Obelisk>(4,0,0,Color::Red));
    pieces.push_back(std::make_unique<Pharoah>(5,0,0,Color::Red));

    pieces.push_back(std::make_unique<Pyramid>(3,2,90,Color::Grey));
    pieces.push_back(std::make_unique<Pyramid>(2,3,0,Color::Grey));
    pieces.push_back(std::make_unique<Pyramid>(2,4,90,Color::Grey));
    pieces.push_back(std::make_unique<Pyramid>(2,7,90,Color::Grey));
    pieces.push_back(std::make_unique<Pyramid>(9,3,90,Color::Grey));
    pieces.push_back(std::make_unique<Pyramid>(9,4,0,Color::Grey));
    pieces.push_back(std::make_unique<Pyramid>(7,6,180,Color::Grey));
    pieces.push_back(std::make_unique<Obelisk>(3,7,0,Color::Grey));
    pieces.push_back(std::make_unique<Obelisk>(5,7,0,Color::Grey));
    pieces.push_back(std::make_unique<Pharoah>(4,7,180,Color::Grey));

    pieces.push_back(std::make_unique<Djed>(4,3,0,Color::Red));
    pieces.push_back(std::make_unique<Djed>(5,3,90,Color::Red));
    pieces.push_back(std::make_unique<Djed>(4,4,90,Color::Grey));
    pieces.push_back(std::make_unique<Djed>(5,4,0,Color::Grey));

    int i = 0;
    for (auto& piece : pieces)
    {
        piece->setIndex(i++);
    }
    qDebug() << "first";
    printPieceLayout();
}

void Game::printPieceLayout() const
{
    qDebug() << "Pieces: (" << (currentTurn == Color::Red ? "red" : "grey")
             << " turn)";
    for (auto& piece : pieces)
    {
        auto pos = piece->position();
        qDebug() << "index:" << piece->index()
                 << "x:" << pos.x << "y:" << pos.y
                 << "angle:" << piece->angle() << "killed:" << piece->isKilled();
    }
}

int Game::isPieceAtPosition(Position pos) const
{
    for (auto& piece : pieces)
    {
        if (piece->position() == pos) return piece->index();
    }
    return false;
}

void Game::endTurn()
{
    calculateBeamCoords(currentTurn == Color::Red ? 0 : 9,
                        currentTurn == Color::Red ? 0 : 7);
    nextTurn();
}

void Game::reset()
{
    currentTurn = Color::Grey;
    pieces.clear();
    startGame();
}

Color Game::getPieceColor(std::size_t index) const
{
    return pieces[index]->color();
}

int Game::possibleTranslationsForPiece(std::size_t index) const
{
    auto& piece = pieces[index];
    int xPos = piece->position().x;
    int yPos = piece->position().y;
    int possibleTranslations = 255;

    // Colored zone restrictions
    if (piece->color() == Color::Red)
    {
        if (xPos == 8)
        {
            possibleTranslations &= ~(Translations::Right |
                Translations::BottomRight | Translations::TopRight);
        }
        else if (xPos == 1)
        {
            if (yPos == 6)
            {
                possibleTranslations &= ~Translations::Bottom;
            }
            else if (yPos == 1)
            {
                possibleTranslations &= ~Translations::Top;
            }
        }
        else if (xPos == 2)
        {
            if (yPos == 6)
            {
                possibleTranslations &= ~Translations::BottomLeft;
            }
            else if (yPos == 7)
            {
                possibleTranslations &= ~Translations::Left;
            }
            else if (yPos == 1)
            {
                possibleTranslations &= ~Translations::TopLeft;
            }
            else if (yPos == 0)
            {
                possibleTranslations &= ~Translations::Left;
            }
        }
    }

    if (piece->color() == Color::Grey)
    {
        if (xPos == 1)
        {
            possibleTranslations &= ~(Translations::Left |
                Translations::BottomLeft | Translations::TopLeft);
        }
        else if (xPos == 8)
        {
            if (yPos == 6)
            {
                possibleTranslations &= ~Translations::Bottom;
            }
            else if (yPos == 1)
            {
                possibleTranslations &= ~Translations::Top;
            }
        }
        else if (xPos == 7)
        {
            if (yPos == 6)
            {
                possibleTranslations &= ~Translations::BottomRight;
            }
            else if (yPos == 7)
            {
                possibleTranslations &= ~Translations::Right;
            }
            else if (yPos == 1)
            {
                possibleTranslations &= ~Translations::TopRight;
            }
            else if (yPos == 0)
            {
                possibleTranslations &= ~Translations::Right;
            }
        }
    }

    if (xPos == 0) {
        possibleTranslations &= ~(Translations::Left |
            Translations::BottomLeft | Translations::TopLeft);
    }
    if (xPos == 9) {
        possibleTranslations &= ~(Translations::Right |
            Translations::BottomRight | Translations::TopRight);
    }
    if (piece->position().y == 0) {
        possibleTranslations &= ~(Translations::Top |
            Translations::TopLeft | Translations::TopRight);
    }
    if (piece->position().y == 7) {
        possibleTranslations &= ~(Translations::Bottom |
            Translations::BottomLeft | Translations::BottomRight);
    }

    for (auto& otherPiece : pieces)
    {
        if ((piece->canSwap() && otherPiece->type() == PieceType::Pyramid) ||
                otherPiece->isKilled())
            continue;
        if (otherPiece->position().x == xPos - 1) {
            if (otherPiece->position().y == piece->position().y + 1)
            {
                possibleTranslations &= ~(Translations::BottomLeft);
            }
            else if (otherPiece->position().y == piece->position().y - 1)
            {
                possibleTranslations &= ~(Translations::TopLeft);
            }
            else if (otherPiece->position().y == piece->position().y)
            {
                possibleTranslations &= ~(Translations::Left);
            }
        }
        else if (otherPiece->position().x == piece->position().x + 1) {
            if (otherPiece->position().y == piece->position().y + 1)
            {
                possibleTranslations &= ~(Translations::BottomRight);
            }
            else if (otherPiece->position().y == piece->position().y - 1)
            {
                possibleTranslations &= ~(Translations::TopRight);
            }
            else if (otherPiece->position().y == piece->position().y)
            {
                possibleTranslations &= ~(Translations::Right);
            }
        }
        else if (otherPiece->position().x == piece->position().x &&
                 otherPiece->position().y == piece->position().y + 1)
        {
            possibleTranslations &= ~(Translations::Bottom);
        }
        else if (otherPiece->position().x == piece->position().x &&
                 otherPiece->position().y == piece->position().y - 1)
        {
            possibleTranslations &= ~(Translations::Top);
        }
    }
    return possibleTranslations;
}

void Game::updatePiecePosition(std::size_t index, int x, int y)
{
    auto& piece = pieces[index];
    if (int otherIndex = isPieceAtPosition(Position{x,y}))
    {
        pieces[otherIndex]->setPosition(piece->position());
    }
    piece->setPosition(x,y);
}

void Game::updatePieceAngle(std::size_t index, int angle)
{
//    qDebug() << "index:" << index;
    auto& piece = pieces[index];
    piece->setAngle(angle);
}

bool isBeamVertical(int& reflections)
{
    return reflections % 2 == 0;
}

QList<int> Game::calculateBeamCoords(int startX, int startY)
{
    // Coords in sets of 3:
    // 0 - Xcoord
    // 1 - Ycoord
    // 2 - Termination Type (0 is wall, 1 is piece)

    QList<int> coords;
    Piece* targetPiece = nullptr;
    bool terminated = false;
    Position reflectorPosition = Position{startX, startY == 0 ? -1 : 8};
    Direction laserDirection = startY == 0 ? Direction::PosY : Direction::NegY;
    int reflections = 0;
    while (!terminated)
    {
        // Path search
        for (const auto& piece : pieces)
        {
            bool pieceIsNotKilled = !piece->isKilled();
            bool pieceIsInPathOfBeam = isBeamVertical(reflections) ?
                        piece->position().x == reflectorPosition.x :
                        piece->position().y == reflectorPosition.y;
            bool pieceIsAheadOfReflector = isBeamVertical(reflections) ? (laserDirection == Direction::NegY ?
                       piece->position().y < reflectorPosition.y :
                       piece->position().y > reflectorPosition.y) :
                       (laserDirection == Direction::NegX ?
                       piece->position().x < reflectorPosition.x :
                       piece->position().x > reflectorPosition.x);

            if (pieceIsNotKilled && pieceIsInPathOfBeam &&
                pieceIsAheadOfReflector)
            {
                if (targetPiece == nullptr)
                {
                    targetPiece = piece.get();
                    continue;
                }
                bool pieceIsAheadOfTargetPiece = isBeamVertical(reflections) ? (laserDirection == Direction::NegY ?
                           piece->position().y > targetPiece->position().y :
                           piece->position().y < targetPiece->position().y) :
                           (laserDirection == Direction::NegX ?
                           piece->position().x > targetPiece->position().x :
                           piece->position().x < targetPiece->position().x);
                if (pieceIsAheadOfTargetPiece)
                {
                    targetPiece = piece.get();
                }
            }
        }
        // No piece in path
        if (targetPiece == nullptr)
        {
            if (debugInfo) qDebug() << "Beam hit wall";

            if (isBeamVertical(reflections))
            {
                int opposingWallY = laserDirection == Direction::NegY ? 0 : 7;
                coords << reflectorPosition.x << opposingWallY << 0;
            }
            else {
                int opposingWallX = laserDirection == Direction::NegX ? 0 : 9;
                coords << opposingWallX << reflectorPosition.y << 0;
            }
            terminated = true;
            break;
        }
        // Piece intercepted
        else
        {
            coords << targetPiece->position().x << targetPiece->position().y << 1;
            Interaction targetPieceInteraction = targetPiece->laserInteraction(laserDirection);
            int targetPieceIndex = targetPiece->index();
            switch (targetPieceInteraction)
            {
            case Interaction::Kill:
                if (debugInfo) qDebug() << "Piece" << targetPieceIndex << "Killed";
                if (targetPiece->canStack() && targetPiece->isStacked())
                {
                    targetPiece->unstack();
                    emit unstackPiece(targetPieceIndex,
                                      targetPiece->color() == Color::Red ? "red" : "grey");
                }
                else
                {
                    targetPiece->setKilled();
                    emit pieceKilled(targetPieceIndex);
                    if (targetPiece->type() == PieceType::Pharoah)
                    {
                        gameOver = true;
                        emit pharoahKilled(targetPieceIndex);
                    }
                }
                terminated = true;
                break;
            case Interaction::ReflectNegX:
                if (debugInfo) qDebug() << "Piece" << targetPieceIndex << "Reflecting NegX";
                laserDirection = Direction::NegX;
                break;
            case Interaction::ReflectPosX:
                if (debugInfo) qDebug() << "Piece" << targetPieceIndex << "Reflecting PosX";
                laserDirection = Direction::PosX;
                break;
            case Interaction::ReflectNegY:
                if (debugInfo) qDebug() << "Piece" << targetPieceIndex << "Reflecting NegY";
                laserDirection = Direction::NegY;
                break;
            case Interaction::ReflectPosY:
                if (debugInfo) qDebug() << "Piece" << targetPieceIndex << "Reflecting PosY";
                laserDirection = Direction::PosY;
                break;
            case Interaction::Error:
                if (debugInfo) qDebug() << "Piece" << targetPieceIndex << "Interaction error";
            }
            reflections++;
            reflectorPosition = targetPiece->position();
            // Clearing to hand off targetPiece to next target
            targetPiece = nullptr;
        }
    }
    return coords;
}
