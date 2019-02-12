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

Game::Game(Game& newGame)
    : pieces(newGame.pieces), currentTurn(newGame.currentTurn),
      lastMove(newGame.lastMove)
{

}

void Game::startGame()
{
    pieces.push_back(std::make_shared<Pyramid>(7,0,270,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(2,1,0,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(0,3,180,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(0,4,270,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(6,5,270,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(7,3,270,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(7,4,180,Color::Red));
    pieces.push_back(std::make_shared<Obelisk>(6,0,0,Color::Red));
    pieces.push_back(std::make_shared<Obelisk>(4,0,0,Color::Red));
    pieces.push_back(std::make_shared<Pharoah>(5,0,0,Color::Red));

    pieces.push_back(std::make_shared<Pyramid>(3,2,90,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(2,3,0,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(2,4,90,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(2,7,90,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(9,3,90,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(9,4,0,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(7,6,180,Color::Grey));
    pieces.push_back(std::make_shared<Obelisk>(3,7,0,Color::Grey));
    pieces.push_back(std::make_shared<Obelisk>(5,7,0,Color::Grey));
    pieces.push_back(std::make_shared<Pharoah>(4,7,180,Color::Grey));

    pieces.push_back(std::make_shared<Djed>(4,3,0,Color::Red));
    pieces.push_back(std::make_shared<Djed>(5,3,90,Color::Red));
    pieces.push_back(std::make_shared<Djed>(4,4,90,Color::Grey));
    pieces.push_back(std::make_shared<Djed>(5,4,0,Color::Grey));

    int i = 0;
    for (auto& piece : pieces)
    {
        piece->setIndex(i++);
    }
}

void Game::reset()
{
    currentTurn = Color::Grey;
    pieces.clear();
    startGame();
}

bool Game::operator==(const Game &otherGame)
{
    auto otherPieces = otherGame.getPieces();
    if (otherPieces.size() == pieces.size())
    {
        for(std::size_t i = 0; i < pieces.size(); i++)
        {
            if (pieces[i] != otherPieces[i]) return false;
        }
        return true;
    }
    return false;
}

Color Game::getPieceColor(std::size_t index) const
{
    return pieces[index]->color();
}

int Game::possibleTranslationsForPiece(std::size_t index)
{
    std::shared_ptr<Piece> piece = pieces[index];
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

    for (auto otherPiece : pieces)
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
    piece->setPosition(x,y);
}

void Game::updatePieceAngle(std::size_t index, int angle)
{
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
    std::shared_ptr<Piece> targetPiece = nullptr;
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
                    targetPiece = piece;
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
                    targetPiece = piece;
                }
            }
        }
        // No piece in path
        if (targetPiece == nullptr)
        {
            qDebug() << "Beam hit wall";

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
                qDebug() << "Piece" << targetPieceIndex << "Killed";
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
                        emit pharoahKilled(targetPieceIndex);
                    }
                }
                terminated = true;
                break;
            case Interaction::ReflectNegX:
                qDebug() << "Piece" << targetPieceIndex << "Reflecting NegX";
                laserDirection = Direction::NegX;
                break;
            case Interaction::ReflectPosX:
                qDebug() << "Piece" << targetPieceIndex << "Reflecting PosX";
                laserDirection = Direction::PosX;
                break;
            case Interaction::ReflectNegY:
                qDebug() << "Piece" << targetPieceIndex << "Reflecting NegY";
                laserDirection = Direction::NegY;
                break;
            case Interaction::ReflectPosY:
                qDebug() << "Piece" << targetPieceIndex << "Reflecting PosY";
                laserDirection = Direction::PosY;
                break;
            case Interaction::Error:
                qDebug() << "Piece" << targetPieceIndex << "Interaction error";
            }
            reflections++;
            reflectorPosition = targetPiece->position();
            // Clearing to hand off targetPiece to next target
            targetPiece = nullptr;
        }
    }
    return coords;
}
